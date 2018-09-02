/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  HSLAPixel::HSLAPixel(){
    s=h=0;
    a=l=1;
  }
  HSLAPixel::HSLAPixel(double hu, double sa, double lu){
    h=hu;
    s=sa;
    l=lu;
    a=1;
  }
  HSLAPixel::HSLAPixel(double hu, double sa, double lu, double al){
    h=hu;
    s=sa;
    l=lu;
    a=al;
  }
}
