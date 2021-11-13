#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include <boost/program_options.hpp>

#include <Eigen/Dense>
using Eigen::MatrixXd;

#include "ppm_format.h"
#include "image.h"
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

int main(int argc, char* argv[])
{
   ProgramOptions po = parseProgramOptions(argc, argv);
   string filename = po.image_filename;
   string filename_prefix = filename.substr(0, filename.find_first_of('.'));

   Image2uc img = loadPpmImage("../" + filename_prefix + ".ppm");
   writePpmImage("../" + filename_prefix + "_identity.ppm", img);

   Image2uc bw = applyBlackAndWhite(img);
   writePpmImage("../" + filename_prefix + "_bw.ppm", bw);

   Image2uc bin = applyBinaryColor(bw);
   writePpmImage("../" + filename_prefix + "_bin.ppm", bin);

   Image2uc res = applyErrorDiffusionDithering(bw);
   writePpmImage("../" + filename_prefix + "_errordiffusion.ppm", res);

   cout << "done" << endl;

  return 0;
}

