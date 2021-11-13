#ifndef __IMAGE_FILTERS_H__
#define __IMAGE_FILTERS_H__

#include "image.h"

Image2uc applyErrorDiffusionDithering(const Image2uc& image);
Image2uc applyBinaryColor(const Image2uc& image);
Image2uc applyBlackAndWhite(const Image2uc& image);

#endif