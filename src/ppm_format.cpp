#include "ppm_format.h"

#include <string>
#include <fstream>
using namespace std;

#include "image.h"

Image2uc loadPpmImage(string filename)
{
  ifstream file;
  file.open(filename);
  string line = "";
  getline(file, line); // P6
  getline(file, line); // comment

  size_t sizex = 0, sizey = 0;
  file >> sizex >> sizey;

  size_t bitdepth = 0;
  file >> bitdepth;

  Image2uc result = createImage<unsigned char>(sizex, sizey);

  for (int y=0; y<sizey; ++y)
  {
    for (int x=0; x<sizex; ++x)
    {
      char r,g,b;
      file.read(&r,1);
      file.read(&g,1);
      file.read(&b,1);
      result[y][x].r = r;
      result[y][x].g = g;
      result[y][x].b = b;
    }
  }

  file.close();

  return result;
}

void writePpmImage(string filename, const Image2uc& image)
{
  size_t sizey = image.size();
  if (sizey == 0)
  {
    return;
  }
  size_t sizex = image[0].size();

  ofstream file;
  file.open(filename);

  file << "P6\n";
  file << "# written by neckutrek's super awesome program\n";
  file << sizex << " " << sizey << "\n";
  file << "255\n";

  for (int y=0; y<sizey; ++y)
  {
    for (int x=0; x<sizex; ++x)
    {
      char r = image[y][x].r;
      char g = image[y][x].g;
      char b = image[y][x].b;
      file.write(&r,1);
      file.write(&g,1);
      file.write(&b,1);
    }
  }

  file.close();
}

