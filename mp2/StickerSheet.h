/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
 class StickerSheet{
 public:
   StickerSheet(const Image &picture, unsigned max);
   ~StickerSheet();
   StickerSheet(const StickerSheet &other);
   const StickerSheet& operator=(const StickerSheet &other);
   void changeMaxStickers(unsigned max);
   int addSticker(Image &sticker, unsigned x, unsigned y);
   bool translate(unsigned index, unsigned x, unsigned y);
   void removeSticker(unsigned index);
   Image * getSticker (unsigned index) const;
   Image render() const;
private:
  struct sticker{
    Image* im;
    unsigned x;
    unsigned y;
  };
  sticker* stickers_;
  Image basePic_;
  unsigned count_,max_;
  void _copy(const StickerSheet& ss);
  void _delete();
 };
