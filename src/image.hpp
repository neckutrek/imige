#ifndef __LIBPIPELINE_IMAGE_H__
#define __LIBPIPELINE_IMAGE_H__

#include <vector>
#include <algorithm>
#include <ostream>

#include "element.hpp"

template <typename T> class Image;

template <typename T>
Image<T> createImage(size_t sizex, size_t sizey, const Element<T>& el);

template <typename T>
class Image
{
private:
   using DataT = std::vector<std::vector< Element<T> >>;

   DataT m_data;

public:

   auto size() const
   {
      size_t sizey = m_data.size();
      size_t sizex = 0;
      if (sizey > 0)
      {
         sizex = m_data[0].size();
      }
      return std::tuple<size_t, size_t>{sizex, sizey};
   }

public:

   Element<T>& operator()(size_t idx1, size_t idx2)
   {
      return m_data[idx2][idx1];
   }

   const Element<T>& operator()(size_t idx1, size_t idx2) const
   {
      return m_data[idx2][idx1];
   }

public:

   friend Image<T> createImage<T>(size_t, size_t,const Element<T>&);

};

using Image2uc = Image<unsigned char>;
using Image2i = Image<int>;
using Image2d = Image<double>;

template <typename T>
Image<T> createImage(size_t sizex, size_t sizey, const Element<T>& el)
{
   Image<T> result;
   result.m_data.resize(sizey);
   for (size_t i=0; i<sizey; ++i)
   {
      result.m_data[i].resize(sizex);
      fill(begin(result.m_data[i]), end(result.m_data[i]), el);
   }
   return result;
}

template <typename T>
Image<T> createImage(size_t sizex, size_t sizey, Element<T>&& el)
{
   return createImage(sizex, sizey, el);
}

template <typename T>
Image<T> createImage(size_t sizex, size_t sizey)
{
   return createImage(sizex, sizey, Element<T>{0,0,0});
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Image<T>& img)
{
   size_t sizey = img.size();
   if (sizey == 0)
   {
      return os;
   }
   size_t sizex = img[0].size();

   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         os << img(x,y) << "   ";
      }
      os << "\n";
   }

   return os;
}

#endif