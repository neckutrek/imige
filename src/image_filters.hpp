#ifndef IMAGE_FILTERS_HPP
#define IMAGE_FILTERS_HPP

#include "element_filters.hpp"
#include "image.hpp"
#include "palette.hpp"

#include <iostream>
#include <iomanip>
using namespace std;

template <typename T, typename Function>
Image<T> transform(const Image<T>& image, Function function)
{
   auto [sizex, sizey] = image.size();

   auto result = createImage<T>(sizex, sizey);
   for (size_t y = 0; y < sizey; ++y)
   {
      for (size_t x = 0; x < sizex; ++x)
      {
         result(x,y) = function(image(x,y));
      }
   }

   return result;
}

template <typename T>
Image<T> dither(const Image<T>& image, const Palette<T>& palette)
{
   auto [sizex, sizey] = image.size();

   Image2d semiimage = createImage<double>(sizex, sizey);
   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         semiimage(x,y) = Element<double>( image(x,y) );
      }
   }

   Image<T> result = createImage<T>(sizex, sizey);

   Image2d semiresult = createImage<double>(sizex, sizey);
   Image2d error = createImage<double>(sizex+2, sizey+2);
   Image2d dbgimg = createImage<double>(sizex+2,sizey+2);

   Palette<double> palette_d;
   for (const auto& el : palette)
   {
      palette_d.push_back( Element<double>(el) );
   }

   for (size_t y = 0; y < sizey; ++y)
   {
      for (size_t x = 0; x < sizex; ++x)
      {
         semiresult(x,y) = getNearestNeighbour( semiimage(x,y)+error(x+1,y+1), palette_d );
         Element<double> err = semiimage(x,y) - semiresult(x,y);

         error(x+2,y+1) += err * (7.0/16.0);
         error(x,y+2) += err * (1.0/16.0);
         error(x+1,y+2) += err * (5.0/16.0);
         error(x+2,y+2) += err * (3.0/16.0);

      }
   }

   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         result(x,y) = Element<T>( semiresult(x,y) );
      }
   }
   return result;
}

#endif