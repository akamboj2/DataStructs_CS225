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

  unsigned x=point.x,y=point.y;
  Point neighbors[4]={Point(x+1,y),Point(x,y+1),Point(x-1,y),Point(x,y-1)};
  for (Point n : neighbors){
    for (Point v : visited_){
      if (v==n) continue; //if we already visited point... just continue to the next
    }
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

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point top = items_.front();
  visited_.push_back(top);
  items_.pop_back();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return items_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return items_.empty();
}
