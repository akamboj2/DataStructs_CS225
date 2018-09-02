/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#ifndef CS225_HSLAPIXEL_H_
#define CS225_HSLAPIXEL_H_

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel{
    public:
      HSLAPixel();
      HSLAPixel(double hu, double sa, double lu);
      HSLAPixel(double hu, double sa, double lu, double al);
      double h,s,l,a;
  };
}

#endif
