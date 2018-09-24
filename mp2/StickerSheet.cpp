#include "StickerSheet.h"
#include "Image.h"
using namespace std;
StickerSheet::StickerSheet(const Image & pic, unsigned max) : max_(max){
  basePic_=pic;
  stickers_=new sticker[max_];
  for (unsigned i=0;i<max_;i++){
    stickers_[i].im=NULL;
  }
  count_=0;
}

StickerSheet::~StickerSheet(){
  _delete();
}
StickerSheet::StickerSheet(const StickerSheet &other){
  _copy(other);
}
const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
  _delete();
  _copy(other);
  return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){
  //copy stickers array to new stickers array of longer length
  sticker* oldcopy=stickers_;
  stickers_= new sticker[max];
  unsigned copyto=(max<count_ ? max:count_);
  for (unsigned i=0;i<copyto;i++){
    stickers_[i]=oldcopy[i];
    stickers_[i].im =new Image(*(oldcopy[i].im));
    delete oldcopy[i].im;
    //can ignore line below bc within count all the stickers should not be null
    //stickers_[i].im = ((oldcopy[i].im==NULL) ? NULL:new Image(*(oldcopy[i].im)));
  }
  //case of resizing to less stickers then you need to delete the excess stickers
  if (max<count_){
    for (unsigned i=max_;i<count_;i++){
      delete oldcopy[i].im;
    };
    count_=max;//if you resize it to less then count, then your new count is max!
  }
  delete [] oldcopy;
  max_=max;
}
void StickerSheet::_delete(){
  for(unsigned i=0;i<count_;i++){
    delete stickers_[i].im;
  }
  delete [] stickers_;
}
void StickerSheet::_copy(const StickerSheet& ss){
  basePic_=ss.basePic_;
  max_=ss.max_;
  count_=ss.count_;
  stickers_=new sticker[max_];
  for (unsigned i=0;i<max_;i++){
    stickers_[i].im=NULL;
  }
  for (unsigned i=0;i<count_;i++){
    stickers_[i].im= new Image(*(ss.stickers_[i].im));
    stickers_[i].x=ss.stickers_[i].x;
    stickers_[i].y=ss.stickers_[i].y;
  }
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  if (count_==max_) return -1;
  stickers_[count_].im= new Image(sticker);//&sticker;//new Image;
  //*(stickers_[count_].im)=(sticker);
  stickers_[count_].x=x;
  stickers_[count_].y=y;

  return count_++;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if (index>max_ || stickers_[index].im==NULL) return false;
  stickers_[index].x=x;
  stickers_[index].y=y;
  return true;
}
void StickerSheet::removeSticker(unsigned index){
  if (index<max_ && stickers_[index].im!=NULL){//check to make sure sticker is actually there
    //loop from index to end of array copying the stickers down.
    delete stickers_[index].im;
    for (unsigned i=index+1;i<count_;i++){
      stickers_[i-1]=stickers_[i];
    }
    stickers_[count_-1].im=NULL; //the last one would be left with the second to last one (two sticker copies of the same thing)
    count_--;
  }
}
Image * StickerSheet::getSticker (unsigned index) const{
  if (index>=max_ || stickers_[index].im==NULL) return NULL;//check to make sure sticker is actually there
  return stickers_[index].im;
}
Image StickerSheet::render() const{
  //find the max width and height;
  unsigned maxw=basePic_.width(),maxh=basePic_.height();
  for (unsigned i=0;i<count_;i++){
    unsigned pwidth=stickers_[i].im->width()+stickers_[i].x;
    maxw=(pwidth>maxw ? pwidth:maxw);
    unsigned pheight=stickers_[i].im->height()+stickers_[i].y;
    maxh=(pheight>maxh ? pheight:maxh);
  }
//  cout<<"calced dims:"<<maxw<<","<<maxh<<endl;
  Image sheet;
  sheet.resize(maxw,maxh);
  //copy basePic_
  for (unsigned x=0;x<basePic_.width();x++){
    for(unsigned y=0;y<basePic_.height();y++){
      HSLAPixel & pix = sheet.getPixel(x,y);
      pix=basePic_.getPixel(x,y);
    }
  }

//  cout<<"count is "<<count_<<endl;
  //copy the rest of the pictures
  for (unsigned i=0;i<count_;i++){
//    cout<<"Adding sticker at "<<stickers_[i].x<<","<<stickers_[i].y<<endl;
    for (unsigned x=0;x<stickers_[i].im->width();x++){
      for (unsigned y=0;y<stickers_[i].im->height();y++){
        HSLAPixel & pix = sheet.getPixel(x+stickers_[i].x,y+stickers_[i].y);
        HSLAPixel & copypix=stickers_[i].im->getPixel(x,y);
        if (copypix.a!=0){
          pix=copypix;
        }
      }
    }
  }

  return sheet;
}
