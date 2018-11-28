#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;

    SquareMaze m;
    m.makeMaze(30,30);
    PNG* a =m.drawMazeWithSolution();
    //unsigned offset=0;
    PNG* b = new PNG(a->width()*2,a->height());

    for(unsigned y=0;y<a->height();y++){//just shift over the maze
      for(unsigned x=0;x<a->width();x++){
      b->getPixel(x+y,y)=a->getPixel(x,y);
      }
    }

    b->writeToFile("creative.png");
    delete a;
    delete b;
    return 0;
}
