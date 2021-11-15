#ifndef ELEMENT_FILTERS_HPP
#define ELEMENT_FILTERS_HPP

#include "element.hpp"
#include "palette.hpp"

#include <map>
#include <cmath>

template <typename T>
double getDistance(const Element<T>& el1, const Element<T>& el2)
{
   if constexpr(std::is_signed_v<T>)
   {
      Element<T> diff = el1 - el2;
      return std::sqrt( diff.r*diff.r + diff.g*diff.g + diff.b*diff.b );
   }
   else
   {
      auto absdiff = [](const T& t1, const T& t2){
         return std::max(t1, t2) - std::min(t1, t2);
      };
      T dr = absdiff(el1.r, el2.r);
      T dg = absdiff(el1.g, el2.g);
      T db = absdiff(el1.b, el2.b);
      return std::sqrt( dr*dr + dg*dg + db*db);
   }
   return .0;
}

template <typename T>
Element<T> getNearestNeighbour(const Element<T>& el, const Palette<T>& palette)
{
   if (palette.empty())
   {
      return el;
   }

   std::multimap<double, const Element<T>&> distance_map;
   for (const auto& p : palette)
   {
      distance_map.insert( {getDistance(el, p), p} );
   }
   return distance_map.begin()->second;
}

#endif