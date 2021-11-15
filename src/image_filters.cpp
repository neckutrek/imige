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
   auto [sizex, sizey] = image.size();

   Image2uc result = createImage<unsigned char>(sizex, sizey);
   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         result(x,y) = getBlackWhiteColor<unsigned char>(image(x,y));
      }
   }

   return result;
}
