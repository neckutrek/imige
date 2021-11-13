#include "fileformats.hpp"

template <typename T, ImageStreamType StreamType, class CharT>
Image<T> readStream(std::basic_istream<CharT>& is)
{
   static_assert(StreamType == ImageStreamType::PPM);

   string line = "";
   getline(is, line); // P6
   getline(is, line); // comment

   size_t sizex = 0, sizey = 0;
   is >> sizex >> sizey;

   size_t bitdepth = 0;
   is >> bitdepth;

   auto result = createImage<T>(sizex, sizey);

   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         char r,g,b;
         is.read(&r,1);
         is.read(&g,1);
         is.read(&b,1);
         result[y][x].r = static_cast<T>(r);
         result[y][x].g = static_cast<T>(g);
         result[y][x].b = static_cast<T>(b);
      }
   }
   return result;
}

template <typename T, ImageStreamType StreamType, class CharT>
void writeStream(const Image<T>& image, std::basic_ostream<CharT>& os)
{
   static_assert(StreamType == ImageStreamType::PPM);

   size_t sizey = image.size();
   if (sizey == 0)
   {
      return;
   }
   size_t sizex = image[0].size();

   os << "P6\n";
   os << "# written by neckutrek's super awesome program\n";
   os << sizex << " " << sizey << "\n";
   os << "255\n";

   for (size_t y=0; y<sizey; ++y)
   {
      for (size_t x=0; x<sizex; ++x)
      {
         char r = static_cast<char>(image[y][x].r);
         char g = static_cast<char>(image[y][x].g);
         char b = static_cast<char>(image[y][x].b);
         os.write(&r,1);
         os.write(&g,1);
         os.write(&b,1);
      }
   }
}
