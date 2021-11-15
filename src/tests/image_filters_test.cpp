#include "catch.hpp"
#include "catch_utils.hpp"

#include "image_filters.hpp"

#include <iostream>
#include <string>

TEST_CASE("dither", "[image_filters]")
{
   size_t sizey = 30;
   size_t sizex = 40;

   {
      auto image = createImage<unsigned char>(sizex, sizey, Element<unsigned char>{0x80,0x80,0x80});
      Palette<unsigned char> palette{ {0,0,0}, {0xff,0xff,0xff} };
      auto result = dither(image, palette);
      for (size_t y=0; y<sizey; ++y)
      {
         for (size_t x=0; x<sizex; ++x)
         {
            size_t pidx = ( (x%2 == y%2) ? 1 : 0);
            std::string errmsg = "dither uchar: invalid element at index (" + std::to_string(x) + "," + std::to_string(y) + ")";
            REQUIRE_MESSAGE( result[y][x] == palette[pidx], errmsg);
         }
      }
   }

   {
      auto image = createImage<double>(sizex, sizey, Element<double>{.5,.5,.5});
      Palette<double> palette{ {0,0,0}, {1,1,1} };
      auto result = dither(image, palette);
      for (size_t y=0; y<sizey; ++y)
      {
         for (size_t x=0; x<sizex; ++x)
         {
            size_t pidx = ( (x%2 == y%2) ? 0 : 1);
            std::string errmsg = "dither double: invalid element at index (" + std::to_string(x) + "," + std::to_string(y) + ")";
            REQUIRE_MESSAGE( result[y][x] == palette[pidx], errmsg);
         }
      }
   }
}