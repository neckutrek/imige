#include "catch.hpp"
#include "catch_utils.hpp"

#include "fileformats.hpp"

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

TEST_CASE("ppm format read and write", "[fileformats]")
{
   size_t sizey = 3;
   size_t sizex = 4;

   string str = R"STR(P6
# Created by GIMP version 2.10.22 PNM plug-in
4 3
255
������������������������������������)STR";
   stringstream ss{str};

   auto image = readStream<unsigned char, ImageStreamType::PPM>(ss);

   REQUIRE( image.size() == sizey );
   REQUIRE( image[0].size() == sizex );

   stringstream ss2;
   writeStream<unsigned char, ImageStreamType::PPM>(image, ss2);
   string str2 = ss2.str();

   stringstream ss3{str2};
   auto image2 = readStream<unsigned char, ImageStreamType::PPM>(ss3);

   REQUIRE( image.size() == image2.size() );
   REQUIRE( image[0].size() == image2[0].size() );

   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         REQUIRE_MESSAGE(image[y][x] == image2[y][x], "Images differ at (" + to_string(x) + "," + to_string(y) + ")");
      }
   }
}