#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance)
: start_(start),pic_(png),tol_(tolerance){
  /** @todo [Part 1] */
//  cout<<"initialization: "<<start<<'\n';
  items_.push_back(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* bfs= new BFS(pic_,start_,tol_);
  return ImageTraversal::Iterator(bfs,start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
//  cout<<"Enque from add: "<<point<<endl;
  items_.insert(items_.begin(),point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */

  Point back = items_.back();
//  cout<<"dequeing back"<<back<<"\n";
  visited_.push_back(back);
  //cout<<"Items_: "<<items_.back()<<"\n";
  items_.pop_back();
  //cout<<items_.back()<<endl;

  //just moved the logic for adding neighbors down here
  //needed to do such to get first few test cases to work!
  Point point=back;
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
  //    cout<<"enquing in pop() (adding neighbors) "<<n<<'\n';
      items_.insert(items_.begin(),n);
    }else{
//      cout<<"NOT IN DELTA\n";
    }
  }


  return back;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return items_.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return items_.empty();
}
