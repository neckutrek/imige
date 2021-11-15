#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <cmath>

template <typename T>
struct Element
{
   T r,g,b;

   template<typename T2>
   operator Element<T2>() const
   {
      return Element<T2>{
         static_cast<T2>(this->r),
         static_cast<T2>(this->g),
         static_cast<T2>(this->b)
      };
   }
};

template <typename T>
Element<T> operator+(const Element<T>& p1, const Element<T>& p2)
{
   return Element<T>{
      p1.r + p2.r,
      p1.g + p2.g,
      p1.b + p2.b
   };
}

template <typename T>
void operator+=(Element<T>& p1, const Element<T>& p2)
{
   p1 = p1 + p2;
}

template <typename T>
Element<T> operator-(const Element<T>& p1, const Element<T>& p2)
{
   return Element<T>{
      p1.r - p2.r,
      p1.g - p2.g,
      p1.b - p2.b
   };
}

template <typename T>
Element<T> operator/(const Element<T>& p1, T t)
{
   return Element<T>{
      p1.r / t,
      p1.g / t,
      p1.b / t
   };
}

template <typename T>
bool operator==(const Element<T>& p1, const Element<T>& p2)
{
   return p1.r == p2.r && p1.g == p2.g && p1.b == p2.b;
}

template <typename T>
Element<T> operator*(const Element<T>& p1, double d)
{
   auto t = [d](T t) -> T {
      double a = static_cast<double>(t) * d;
      if constexpr(std::is_floating_point_v<T>)
      {
         return static_cast<T>( a );
      }
      else
      {
         return static_cast<T>( std::round(a) );
      }
   };

   return Element<T>{
      t(p1.r),
      t(p1.g),
      t(p1.b)
   };
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Element<T>& pixel)
{
   os << pixel.r << "," << pixel.g << "," << pixel.b;
   return os;
}

#endif