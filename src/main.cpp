#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include <boost/program_options.hpp>

#include <Eigen/Dense>
using Eigen::MatrixXd;

#include "fileformats.hpp"
#include "image.hpp"
#include "image_filters.h"

struct ProgramOptions
{
   string image_filename;
};

ProgramOptions parseProgramOptions(int argc, char* argv[])
{
   ProgramOptions result;

   using namespace boost::program_options;
   try
   {
      options_description desc{"Options"};
      desc.add_options()
         ("help,h", "Help screen")
         ("img", value<string>()->default_value(""), "Image filename");

      variables_map vm;
      store(parse_command_line(argc, argv, desc), vm);
      notify(vm);

      if (vm.count("help"))
      {
         cout << desc << endl;
      }

      result.image_filename = vm["img"].as<string>();
   }
   catch(const error& e)
   {
      std::cerr << "Boost program options error: " << e.what() << '\n';
   }

   return result;
}

template <typename T>
Image<T> loadImage(const std::string& filename)
{
   ifstream file;
   file.open(filename);
   if (file.is_open())
   {
      auto result = readStream<T, ImageStreamType::PPM>(file);
      file.close();
      return result;
   }
   file.close();
   return createImage<T>(0,0);
}

template <typename T>
void writeImage(const Image<T>& image, const std::string& filename)
{
   ofstream file;
   file.open(filename);
   if (file.is_open())
   {
      writeStream<T, ImageStreamType::PPM>(image, file);
   }
   file.close();
}

int main(int argc, char* argv[])
{
   ProgramOptions po = parseProgramOptions(argc, argv);
   string filename = po.image_filename;
   string filename_prefix = filename.substr(0, filename.find_first_of('.'));

   Image2uc img = loadImage<unsigned char>("../" + filename_prefix + ".ppm");
   writeImage(img, "../" + filename_prefix + "_identity.ppm");

   Image2uc bw = applyBlackAndWhite(img);
   writeImage(bw, "../" + filename_prefix + "_bw.ppm");

   Image2uc bin = applyBinaryColor(bw);
   writeImage(bin, "../" + filename_prefix + "_bin.ppm");

   Image2uc res = applyErrorDiffusionDithering(bw);
   writeImage(res, "../" + filename_prefix + "_errordiffusion.ppm");

   cout << "done" << endl;

  return 0;
}

