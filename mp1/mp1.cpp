#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>

#include <random>

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG inIm; //create input image
  inIm.readFromFile(inputFile);//read that image from a png file
  int w=inIm.width(), h=inIm.height();
  PNG outIm(w,h); //create an output image with same height and width

  int x2=0,y2=inIm.height()-1; //x2 and y2 are going opposite direction from y and x
  for(int y=0;y<h;y++){//go right to left and bottom up in normal picture
                      //so x2 and y2 are going left to right and top down
    for (int x=w-1;x>=0;x--){
      //std::cout<<"x,y: "<<x<<","<<y<<std::endl;
      HSLAPixel & p = inIm.getPixel(x,y);
    //  std::cout<<"x2,y2: "<<x2<<","<<y2<<std::endl;
      HSLAPixel & newp=outIm.getPixel(x2,y2);
      newp.h=p.h;
      newp.s=p.s;
      newp.l=p.l;
      newp.a=p.a;
      x2++;
    }
    x2=0;
    y2--;
  }

  outIm.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  std::default_random_engine generator;
  std::normal_distribution<double> do1(1,10);
  std::normal_distribution<double> do2(21,10);
  std::normal_distribution<double> db1(226,10);
  std::normal_distribution<double> db2(206,10);
  //std::cout<< width/2-width/8 <<" "<< width/2+width/8 << " "<< height/2+3*height/8 << " "<<height/2-3*height/8<<std::endl;
  for (unsigned x=0;x<width;x++){
    for (unsigned y=0;y<height;y++){
      HSLAPixel & pixel=png.getPixel(x,y);
      //if you make everything random, the picture is kinda gray and ugly
      //instead lets just make the hue gaussian centered at illini Orange and blue!
      unsigned lowx=width/2-width/10,lowy=height/2-3*height/10,highx=width/2+width/10,highy=height/2+3*height/10;
      if ((x>lowx && x<highx && y>lowy && y<highy) ||
          ((x>lowx-width/10 && x<highx+width/10) &&
            ((y>lowy && y<lowy+height/10) || (y>highy-height/10 && y< highy)))){
        if (rand()%2==0){
          pixel.h= db1(generator);//(double)rand()/(double)RAND_MAX*360;
        }else{
          pixel.h=db2(generator);
        }
      }else{
        if (rand()%2==0){
          double n=do2(generator);
          n=(n<0 ? n+360:n);
          pixel.h= n;//(double)rand()/(double)RAND_MAX*360;
        }else{
          pixel.h=do2(generator);
        }
      }
      //std::cout<<pixel.h<<std::endl;
      pixel.s=.5;//(double)rand()/(double)RAND_MAX*100;
      pixel.l=.5;//(double)rand()/(double)RAND_MAX*100;
      pixel.a=1;//(double)rand()/(double)RAND_MAX*100;
    }
  }

  return png;
}
