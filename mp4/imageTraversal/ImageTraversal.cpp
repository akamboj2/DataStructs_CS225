#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator():current_(Point(-1,-1)) {
  trav_=NULL;
  /** @todo [Part 1] */
  //jk need to use it for at end of iterator
  //ignore this and never use it--> how are you gonna traverse without and traversal?
}

/**2 arg constructor**/
ImageTraversal::Iterator::Iterator(ImageTraversal* T, Point p) : current_(p),trav_(T){
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(trav_==NULL) {cout<<"Can't traverse without a traversal!\n";return *this;}
  if(!trav_->empty()){
    current_=trav_->pop();//technically current should already be the top
    //end of pop now add's neighbors
    //trav_->add(current_);//visited it so add it's neighbors

    //now we actually set current to the correct next value
    current_=trav_->peek();//done visiting the previous one let's start visiting the next
//    trav_->updatePrevPix();
  }
  if(trav_->empty()){
    trav_=NULL;//if you at the end of traversal--make it null!
  }
  return *this;

  //still don't think i can add neighbors in here, bc for bfs you don't readd nieghbor if
  //you see a neigbor that you're already planning to visit. In dfs, you dooo!
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //first two cases makes sure we don't segfault
  if(trav_==NULL && other.trav_==NULL) return false; //they both null
  if(trav_==NULL || other.trav_==NULL) return true; //one or the other is null
  return !(current_==other.current_);
}


ImageTraversal::Iterator::~Iterator(){
  if (trav_!=NULL) delete trav_;
}
