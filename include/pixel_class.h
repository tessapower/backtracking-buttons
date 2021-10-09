#ifndef PIXEL_H
#define PIXEL_H

#include <cstdlib>
#include <fstream>
#include <iostream>

class pixel_class {
private:
  int red, green, blue;
  bool exclude; // if true, do not check this pixel
public:
  void loaddata(int v1, int v2, int v3);
  void datatofile(std::fstream &ppmfile);
  int getR() const { return red; }
  int getG() const { return green; }
  int getB() const { return blue; }
  void setexclude(bool ex) { exclude = ex; }
  bool getexclude() { return exclude; }
};

#endif // PIXEL_H
