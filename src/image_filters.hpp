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
   size_t sizey = image.size();
   if (sizey == 0)
   {
      return image;
   }
   size_t sizex = image[0].size();

   auto result = createImage<T>(sizex, sizey);
   for (size_t y = 0; y < sizey; ++y)
   {
      for (size_t x = 0; x < sizex; ++x)
      {
         result[y][x] = function(image[y][x]);
      }
   }

   return result;
}

template <typename T>
Image<T> dither(const Image<T>& image, const Palette<T>& palette)
{
   size_t sizey = image.size();
   if (sizey == 0)
   {
      return image;
   }
   size_t sizex = image[0].size();

   Image2d semiimage = createImage<double>(sizex, sizey);
   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         semiimage[y][x] = Element<double>( image[y][x] );
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
         semiresult[y][x] = getNearestNeighbour( semiimage[y][x]+error[y+1][x+1], palette_d );
         Element<double> err = semiimage[y][x] - semiresult[y][x];

         error[y+1][x+2] += err * (7.0/16.0);
         error[y+2][x  ] += err * (1.0/16.0);
         error[y+2][x+1] += err * (5.0/16.0);
         error[y+2][x+2] += err * (3.0/16.0);

      }
   }

   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         result[y][x] = Element<T>( semiresult[y][x] );
      }
   }
   return result;
}

#endif