#include "catch.hpp"

#include "element_filters.hpp"

#include <cmath>

TEST_CASE("getDistance","[element_filters]")
{
   double answer = std::sqrt(2*2+3*3+4*4);

   {
      Element<int> el1{2,2,2};
      Element<int> el2{4,5,6};
      REQUIRE( getDistance(el1,el2) == answer );
      REQUIRE( getDistance(el2,el1) == answer );
   }

   {
      Element<int> el1{-2, 2,-2};
      Element<int> el2{ 4,-5, 6};
      double answer = std::sqrt(6*6+7*7+8*8);
      REQUIRE( getDistance(el1,el2) == answer );
      REQUIRE( getDistance(el2,el1) == answer );
   }

   {
      Element<unsigned int> el1{2,2,2};
      Element<unsigned int> el2{4,5,6};
      REQUIRE( getDistance(el1, el2) == answer );
      REQUIRE( getDistance(el2, el1) == answer );
   }

   {
      Element<double> el1{2,2,2};
      Element<double> el2{4,5,6};
      REQUIRE( getDistance(el1,el2) == answer );
      REQUIRE( getDistance(el2,el1) == answer );
   }
}

TEST_CASE("getNearestNeighbour", "[element_filters]")
{
   {
      Element<double> el{2,3,4};
      Palette<double> empty_palette;
      REQUIRE( getNearestNeighbour(el, empty_palette) == el );
   }

   {
      Element<double> el{2,3,4};
      Palette<double> palette{
         {1,1,1}, {2,2,2}, {3,3,3}
      };
      auto answer = Element<double>{3,3,3};
      REQUIRE( getNearestNeighbour(el, palette) == answer );
   }
}