#include "catch.hpp"

#include "image.hpp"

TEST_CASE("createImage", "[image]")
{
   size_t sizey = 5;
   size_t sizex = 5;

   {
      Image2i iimg = createImage<int>(sizex, sizey);
      for (size_t y=0; y<sizey; ++y)
      {
         for (size_t x=0; x<sizex; ++x)
         {
            REQUIRE(iimg(x,y) == Element<int>{0,0,0});
         }
      }
   }

   {
      Element<int> el{1,2,3};
      Image2i iimg = createImage<int>(sizex, sizey, el);
      for (size_t y=0; y<sizey; ++y)
      {
         for (size_t x=0; x<sizex; ++x)
         {
            REQUIRE(iimg(x,y) == el);
         }
      }
   }

   {
      Element<double> el{1.,2.,3.};
      Image2d dimg = createImage<double>(sizex, sizey, el);
      for (size_t y=0; y<sizey; ++y)
      {
         for (size_t x=0; x<sizex; ++x)
         {
            REQUIRE(dimg(x,y) == el);
         }
      }
   }
}