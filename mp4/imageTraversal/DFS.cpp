#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance)
        : start_(start),pic_(png),tol_(tolerance){
  /** @todo [Part 1] */
//  cout<<"initialization: "<<start<<'\n';
  items_.push_back(start);
  //this is like you alraedy visited start now so add it's neighbors
//  visited_.push_back(start);
  /*unsigned x=start.x,y=start.y;
  Point neighbors[4]={Point(x+1,y),Point(x,y+1),Point(x-1,y),Point(x,y-1)};
  for (Point n : neighbors){
    if (calculateDelta(pic_.getPixel(n.x,n.y),pic_.getPixel(at_.x,at_.y))){
      items_.push_back(n);
    }
  }*/
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* dfs= new DFS(pic_,start_,tol_);
  return ImageTraversal::Iterator(dfs,start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
/*
  unsigned x=point.x,y=point.y;
  Point neighbors[4]={Point(x+1,y),Point(x,y+1),Point(x-1,y),Point(x,y-1)};
  for (Point n : neighbors){
    if(n.x>pic_.width() || n.y>pic_.height()) return;
    cout<<"Visited size: "<<visited_.size()<<endl;\
    bool visit=true;
    for (Point v : visited_){
      if (v==n) visit&=false; //if we already visited point... just continue to the next
    }
    if (!visit) break;
    if (calculateDelta(pic_.getPixel(n.x,n.y),pic_.getPixel(x,y))){
    //if we haven't visited point and it's within delta push it!
      //but if it's already in the items to visit. delete it and readd it!
      for(vector<Point>::iterator i=items_.begin();i!=items_.end();i++){
        if (*i==n){
          items_.erase(i);
          break;
        }
      }
      items_.push_back(n);
    }
  }
*/
//  cout<<"pushing from add: "<<point<<'\n';
  items_.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point top = items_.back();
//  cout<<"Popping top"<<top<<"\n";
  visited_.push_back(top);
  //cout<<"Items_: "<<items_.back()<<"\n";
  items_.pop_back();
  //cout<<items_.back()<<endl;

  //just moved the logic for adding neighbors down here
  //needed to do such to get first few test cases to work!
  Point point=top;
  unsigned x=point.x,y=point.y;
  Point neighbors[4]={Point(x+1,y),Point(x,y+1),Point(x-1,y),Point(x,y-1)};
  for (Point n : neighbors){
//    cout<<"Checking "<<n<<"\n";
    if(n.x>pic_.width()-1 || n.y>pic_.height()-1){
//      cout<<"OUT OF BOUNDS\n";
      continue;
    }
//    cout<<"Visited size: "<<visited_.size()<<endl;
    bool needToVisit=true;
    for (Point v : visited_){
      if (v==n) needToVisit&=false; //if we already visited point... just continue to the next
    }
    if (!needToVisit){
//      cout<<"ALREADY VISITED!\n";
      continue;
    }
    if (calculateDelta(pic_.getPixel(n.x,n.y),pic_.getPixel(x,y))<tol_){
  //  cout<<"Delta's for pixel "<<n<<" and "<< point<< " is "<<calculateDelta(pic_.getPixel(n.x,n.y),pic_.getPixel(x,y))<<'\n';
  //  cout<<"and tol is "<<tol_<<"\n";
    //if we haven't visited point and delta<tol  push it!
      //but if it's already in the items to visit. delete it and readd it!
      for(vector<Point>::iterator i=items_.begin();i!=items_.end();i++){
        if (*i==n){//compares points
//          cout<<"ALREADY PLANNED TO VISIT, removing and readding\n";
          items_.erase(i);
          break;
        }
      }
//      cout<<"pushing in pop() (adding neighbors) "<<n<<'\n';
      items_.push_back(n);
    }else{
//      cout<<"NOT IN DELTA\n";
    }
  }
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  //if (items_.empty()) return;
  return items_.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return items_.empty();
}
