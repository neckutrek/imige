#include "image.hpp"
#include "image_filters.h"

#include "palette.hpp"
#include "element_filters.hpp"
#include "image_filters.hpp"

#include <limits>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
Element<T> getBlackWhiteColor(const Element<T>& pixel)
{
   int intensity = pixel.r + pixel.g + pixel.b;
   intensity = intensity / 3;
   intensity = min(intensity, 255);
   intensity = max(intensity, 0);
   T inten = static_cast<T>(intensity);
   return {inten, inten, inten};
}

Image2uc applyBlackAndWhite(const Image2uc& image)
{
   size_t sizey = image.size();
   if (sizey == 0)
   {
      return image;
   }
   size_t sizex = image[0].size();

   Image2uc result = createImage<unsigned char>(sizex, sizey);
   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         result[y][x] = getBlackWhiteColor<unsigned char>(image[y][x]);
      }
   }

   return result;
}

Image2uc applyBinaryColor(const Image2uc& image)
{
size_t sizey = image.size();
   if (sizey == 0)
   {
      return image;
   }
   size_t sizex = image[0].size();

   Palette<unsigned char> blackwhite{ {0,0,0}, {255,255,255} };
   Image2uc result = createImage<unsigned char>(sizex, sizey);
   for (size_t y = 0; y < sizey-1; ++y)
   {
      for (size_t x = 0; x < sizex-1; ++x)
      {
         result[y][x] = getNearestNeighbour(image[y][x],blackwhite);
      }
   }

   return result;
}
