#ifndef FILEFORMATS_HPP
#define FILEFORMATS_HPP

#include "image.hpp"

#include <string>
using std::string;

enum ImageStreamType : int
{
   PPM // Portable Pixel Map
};

// readStream

template <typename T, ImageStreamType StreamType, class CharT = char>
Image<T> readStream(std::basic_istream<CharT>& is);

// writeStream

template <typename T, ImageStreamType StreamType, class CharT = char>
void writeStream(const Image<T>& image, std::basic_ostream<CharT>& os);

#include "fileformats.tpp"

#endif