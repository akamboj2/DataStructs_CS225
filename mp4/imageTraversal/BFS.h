/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using namespace std;
/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  void updatePrevPix();


private:
  /** @todo [Part 1] */
  /** add private members here*/
  vector<Point> items_;
  vector<Point> visited_;
  Point start_;
//  const PNG& pic_;
  double tol_;
  HSLAPixel prevPix; /*STILL NEED TO FIX DELTA IN BFS!*/
  //^^don't use updatePrevPix
  PNG origPic;
};
