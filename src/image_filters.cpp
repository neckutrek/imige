#include <vector>
#include <iostream>
using namespace std;

#include "image.h"
#include "image_filters.h"

template <typename T>
PixelRgb<T> getBlackWhiteColor(const PixelRgb<T>& pixel)
{
   int intensity = pixel.r + pixel.g + pixel.b;
   intensity = intensity / 3;
   intensity = min(intensity, 255);
   intensity = max(intensity, 0);
   T inten = static_cast<T>(intensity);
   return {inten, inten, inten};
}

template <typename T, typename S>
PixelRgb<T> getBinaryColor(const PixelRgb<T>& pixel)
{
   auto transform = [](T t) -> T {
      int tt = int(static_cast<unsigned char>(t));
      int max_val = pow(2,sizeof(S)*8);
      return (tt > max_val/2 ? (T)(max_val-1) : 0);
   };

   PixelRgb<T> p{
      transform(pixel.r), transform(pixel.g), transform(pixel.b)
   };
   return p;
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
   for (int y=0; y<sizey; ++y)
   {
      for (int x=0; x<sizex; ++x)
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

   Image2uc result = createImage<unsigned char>(sizex, sizey);
   for (int y = 0; y < sizey-1; ++y)
   {
      for (int x = 0; x < sizex-1; ++x)
      {
         result[y][x] = getBinaryColor<unsigned char, unsigned char>(image[y][x]);
      }
   }

   return result;
}

Image2uc applyErrorDiffusionDithering(const Image2uc& image)
{
   size_t sizey = image.size();
   if (sizey == 0)
   {
      return image;
   }
   size_t sizex = image[0].size();

   Image2uc result = createImage<unsigned char>(sizex, sizey);
   Image2i error = createImage<int>(sizex+2, sizey+2);
   Image2d dbgimg = createImage<double>(sizex+2,sizey+2);

   for (int y = 0; y < sizey; ++y)
   {
      for (int x = 0; x < sizex; ++x)
      {
         /*
         for (int yy=0; yy<sizey; ++yy)
         {
            for (int xx=0; xx<sizex; ++xx)
            {
               dbgimg[yy][xx] = (PixelRgb<double>)(error[yy+1][xx+1]+(PixelRgb<int>)(image[yy][xx])) / 255.0;
            }
         }

         cout << dbgimg << endl << endl;
         */

         result[y][x] = PixelRgb<unsigned char>( getBinaryColor<int, unsigned char>(PixelRgb<int>(image[y][x]) + error[y+1][x+1]) );
         PixelRgb<int> err = PixelRgb<int>(image[y][x]) - PixelRgb<int>(result[y][x]) + error[y+1][x+1];
/*
         error[y+1][x+2] = err *0.5;
         error[y+2][x+1] = err *0.5;
*/
         error[y+1][x+2] = err * (7.0/16.0);
         error[y+2][x  ] = err * (1.0/16.0);
         error[y+2][x+1] = err * (5.0/16.0);
         error[y+2][x+2] = err * (3.0/16.0);

      }
   }
   return result;
}


