// Premier_programme.cpp :
// Mon premier programme utilisant CImg.
#include "CImg.h"
using namespace cimg_library;
int main() {
  CImg<unsigned char> img("kingfisher.bmp");
  img.display("Hello World!");
  return 0;
}
