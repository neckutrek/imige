#ifndef __PPM_FORMAT_H__
#define __PPM_FORMAT_H__

#include "image.h"

#include <string>
using std::string;

Image2uc loadPpmImage(string filename);
void writePpmImage(string filename, const Image2uc& image);

#endif