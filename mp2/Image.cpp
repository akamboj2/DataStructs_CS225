#include "Image.h"


void Image::lighten(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l = (pixel.l<=.9 ? pixel.l+.1:1);
    }
  }
}

void Image::lighten(double a){//note this function copied to saturate
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l = (pixel.l<=1-a ? pixel.l+a:1);
    }
  }
}

void Image::darken(){ //note next two functions copied to desaturate
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l = (pixel.l>=.1 ? pixel.l-.1:0);
    }
  }
}

void Image::darken(double a){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l = (pixel.l>=a ? pixel.l-a:0);
    }
  }
}

void Image::saturate(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = (pixel.s<=.9 ? pixel.s+.1:1);
    }
  }
}

void Image::saturate(double a){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = (pixel.s<=1-a ? pixel.s+a:1);
    }
  }
}

void Image::desaturate(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = (pixel.s>=.1 ? pixel.s-.1:0);
    }
  }
}

void Image::desaturate(double a){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = (pixel.s>=a ? pixel.s-a:0);
    }
  }
}

void Image::grayscale(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s =0;
    }
  }
}
void Image::rotateColor(double d){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.h = pixel.h+d;
      while(pixel.h >360){pixel.h-=360;}
      while(pixel.h<0){pixel.h+=360;}
      //pixel.h-=(pixel.h>360 ? 360:0);//make sure it's in range
    }
  }
}

void Image::illinify(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      //“Illini Orange” has a hue of 11
      //Illini Blue” has a hue of 216
      pixel.h= ((pixel.h>113.5 && pixel.h<293.5) ? 216: 11);
    }
  }
}

void Image::scale(double f){
  Image old=*this;
  resize((unsigned int)(f*width()),(unsigned int)(f*height()));
  double w_ratio=(double)old.width()/(double)width(), h_ratio=(double)old.height()/(double)height();
  //printf("%f, %f",w_ratio,h_ratio);
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & new_pixel = getPixel(x, y);
      new_pixel=old.getPixel(((unsigned int)x*w_ratio),((unsigned int)y*h_ratio));
      //new_pixel=old.getPixel(x/2,y/2);
    }
  }
}

void Image::scale(unsigned w, unsigned h){
  Image old=*this;
  resize((unsigned int)(w*width()),(unsigned int)(h*height()));
  double w_ratio=(double)old.width()/(double)width(), h_ratio=(double)old.height()/(double)height();
  //printf("%f, %f",w_ratio,h_ratio);
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & new_pixel = getPixel(x, y);
      new_pixel=old.getPixel(((unsigned int)x*w_ratio),((unsigned int)y*h_ratio));
      //new_pixel=old.getPixel(x/2,y/2);
    }
  }
}
