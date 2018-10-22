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
  for (Point p : traversal){
    pts_.push_back(p);
  }
  cout<<"size of image traversal is: "<<pts_.size()<<endl;
  color = &colorPicker;
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
  //while(!travs_.empty()){
  //  travs_.back();
  //  cols_.back();
    unsigned count=0;
    animation.addFrame(pic_);
    PNG copy=pic_;
//    copy.writeToFile("MyOut.png");
  //  ImageTraversal* t=&travs_.back();
    //ImageTraversal::Iterator it=  t->begin();
    cout<<"begining traversal of points: "<<endl;
    for(unsigned i=0;i<pts_.size();i++){
      Point p = pts_[i];
      pic_.getPixel(p.x,p.y)= color->getColor(p.x,p.y);
      if((i+1)%frameInterval==0){
//        cout<<"adding a frame at count "<<count<<endl;
        animation.addFrame(pic_);
      }
    }
//     for(Point p :pts_){
//       count++;
//       pic_.getPixel(p.x,p.y)= color->getColor(p.x,p.y);
//       if(count!=0 && (count)%frameInterval==0){
// //        cout<<"adding a frame at count "<<count<<endl;
//         animation.addFrame(pic_);
//       }
//     }
    animation.addFrame(pic_);

//    travs_.pop_back();
//    cols_.pop_back();
//  }
  return animation;
}
