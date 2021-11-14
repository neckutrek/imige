#include "catch.hpp"
#include "catch_utils.hpp"

#include "fileformats.hpp"

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

TEST_CASE("portable pixel map", "[fileformats][ppm-format]")
{
   size_t sizey = 3;
   size_t sizex = 4;
   int element = 125;

   const string ppmfile = [element, sizex, sizey](){
      string result = "P6\n";
      result += "# Created by GIMP version 2.10.22 PNM plug-in\n";
      result += to_string(sizex) + " " + to_string(sizey) + "\n";
      result += "255\n";
      for (size_t i=0; i<sizey*sizex; ++i)
      {
         result += static_cast<char>(element);
      }
      return result;
   }();

   auto getImage = [](const string& str){
      stringstream ss{str};
      return readStream<unsigned char, ImageStreamType::PPM>(ss);
   };

   SECTION("readStream", "")
   {
      auto image = getImage(ppmfile);

      REQUIRE( image.size() == sizey );
      REQUIRE( image[0].size() == sizex );

      for (size_t y=0; y<sizey; ++y)
      {
         for (size_t x=0; x<sizex; ++x)
         {
            unsigned char el = static_cast<unsigned char>(element);
            string errmsg = "readStream: invalid image element at (" +
               to_string(x) + "," + to_string(y) + ") ";
            REQUIRE_MESSAGE( (image[y][x] == Element<unsigned char>{el, el, el}),
               errmsg.c_str());
         }
      }
   }

   SECTION("all the rest", "")
   {
      auto image = getImage(ppmfile);

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
}
