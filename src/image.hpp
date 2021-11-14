#ifndef __LIBPIPELINE_IMAGE_H__
#define __LIBPIPELINE_IMAGE_H__

#include <vector>
#include <algorithm>
#include <ostream>

#include "element.hpp"

template <typename T>
using Image = std::vector<std::vector<Element<T>>>;
using Image2uc = Image<unsigned char>;
using Image2i = Image<int>;
using Image2d = Image<double>;

template <typename T>
Image<T> createImage(size_t sizex, size_t sizey, const Element<T>& el)
{
   Image<T> result;
   result.resize(sizey);
   for (size_t i=0; i<sizey; ++i)
   {
      result[i].resize(sizex);
      fill(begin(result[i]), end(result[i]), el);
   }
   return result;
}

template <typename T>
Image<T> createImage(size_t sizex, size_t sizey, Element<T>&& el)
{
   return createImage(sizex, sizey, el);
}

template <typename T>
Image<T> createImage(size_t sizex, size_t sizey)
{
   return createImage(sizex, sizey, Element<T>{0,0,0});
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Image<T>& img)
{
   size_t sizey = img.size();
   if (sizey == 0)
   {
      return os;
   }
   size_t sizex = img[0].size();

   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         os << img[y][x] << "   ";
      }
      os << "\n";
   }

   return os;
}

#endif