#include "Image.h"
#include "StickerSheet.h"
using namespace std;
int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 50);

  sheet.addSticker(i, 900, 600);
  Image c;    c.readFromFile("colors.png");
  c.scale(.09);
//  sheet.addSticker(c,0,0);
  for (int x=0;x<900;x+=100){
    sheet.addSticker(c,x,700);
  }
  for (int y=0;y<600;y+=100){
    sheet.addSticker(c,950,y);
  }

//  cout<<"ALMA's dim:"<<alma.width()<<","<<alma.height()<<endl;
//  cout<<"i's dim:"<<i.width()<<","<<i.height()<<endl;

  Image sh=sheet.render();
//
  sh.writeToFile("myImage.png");

  return 0;
}
