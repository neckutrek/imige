#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <iomanip>

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
Element<T> operator*(const Element<T>& p1, double d)
{
   auto t = [d](T t) -> T {
      return static_cast<T>( static_cast<double>(t) * d + 0.5 );
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
   os << std::setw(3) << pixel.r << ","
      << std::setw(3) << pixel.g << ","
      << std::setw(3) << pixel.b;
   return os;
}

#endif