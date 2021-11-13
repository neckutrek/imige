#include "catch.hpp"

#include "image.hpp"

TEST_CASE("fill image", "[image]")
{
   size_t sizey = 5;
   size_t sizex = 5;

   Image2i iimg = createImage<int>(sizex, sizey);
   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         REQUIRE(iimg[y][x] == Element<int>{0,0,0});
      }
   }

   Image2d dimg = createImage<double>(sizex, sizey);
   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         REQUIRE(dimg[y][x] == Element<double>{.0,.0,.0});
      }
   }
}