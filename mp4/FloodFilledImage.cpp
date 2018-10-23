#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png):pic_(png) {
  /** @todo [Part 2] */
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker){
  /** @todo [Part 2] */
  //ImageTraversal* t = new
  //ImageTraversal::Iterator it=  traversal.begin();
  //color = colorPicker;
  travs_.push_back(&traversal);
  cols_.push_back(&colorPicker);
//   for (Point p : traversal){
// //     if (p==Point(106,68)) cout<<"YO IT'S EVEN IN FLOODFILL! see "<<p<<endl;
//     pts_.push_back(p);
//   }
//  cout<<"size of image traversal is: "<<pts_.size()<<endl;
//  color = &colorPicker;
//  travs_.insert(travs_.begin(),traversal);
//  cols_.insert(cols_.begin(),colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  for (unsigned j=0;j<travs_.size();j++){

   ImageTraversal::Iterator begin=travs_[j]->begin();
   ImageTraversal::Iterator end = travs_[j]->end();

    unsigned count=0;
    animation.addFrame(pic_);
    PNG copy=pic_;
//    copy.writeToFile("MyOut.png");
  //  ImageTraversal* t=&travs_.back();
    //ImageTraversal::Iterator it=  t->begin();
//    cout<<"begining traversal of points: "<<endl<<endl;
    Point debug=Point(-100,-100);//Point(106,68);
//    for(unsigned i=0;i<pts_.size();i++){
    int i=0;
    for(ImageTraversal::Iterator it=begin; it!=end;++it){
      Point p = *it;
      if (p==debug) cout<<"It's also in animate!! "<<p<<endl;
      if (p==debug) cout<<"Before pixels color was "<<pic_.getPixel(p.x,p.y).h<<endl;
      pic_.getPixel(p.x,p.y)= (cols_.back())->getColor(p.x,p.y);
      if (p==debug) cout<<"Now it's pixels color is "<<pic_.getPixel(p.x,p.y).h<<endl;
      if((i+1)%frameInterval==0){
//        cout<<"adding a frame at i "<<i<<endl;
        animation.addFrame(pic_);
      }
      i++;
    }
    animation.addFrame(pic_);


  }

  return animation;
}
