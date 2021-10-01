#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class pixel_class {
private:
    int red, green, blue;
    bool exclude;  // if true, do not check this pixel
public:
    void loaddata(int v1, int v2, int v3);
    void datatofile(fstream & ppmfile);
    int getR() { return red; }
    int getG() { return green; }
    int getB() { return blue; }
    void setexclude(bool ex) { exclude = ex; }
    bool getexclude() { return exclude; }
};

void loadButtons();

int total, xmin, xmax, ymin, ymax;  // MUST be global if used

int screenx, screeny, maxcolours;   // you must use these
pixel_class picture[600][600];      // you must use this

int main() {

    // Step 1 : read in the image from Buttons.ppm
    loadButtons();

    // Step 2 : identify buttons and draw boxes

    // Step 3 : output the final .ppm file
}

void loadButtons() {
    // load the picture from Buttons.ppm
    int x, y, R, G, B;
    fstream infile;
    string infilename, line;
    infilename = "Buttons.ppm";
    infile.open(infilename.c_str(), fstream::in);
    if (infile.is_open() == false) {
        cout << "ERROR: not able to open " << infilename << endl;
        exit(2);
    }
    getline(infile, line);  // this line is "P3"
    getline(infile, line);  // this line is "# filename"
    infile >> screenx >> screeny;  // this line is the size
    infile >> maxcolours;  // this line is 256
    for (y = 0; y < screeny; y++) {
        for (x = 0; x < screenx; x++) {
            infile >> R >> G >> B;
            picture[x][y].loaddata(R, G, B);
            picture[x][y].setexclude(false);
        }
    }
    infile.close();
}

//--------------- methods for the pixel_class ------------
void pixel_class::loaddata(int v1, int v2, int v3) {
    red = v1;
    green = v2;
    blue = v3;
}

void pixel_class::datatofile(fstream & ppmfile) {
    // write the data for one pixel to the ppm file
    ppmfile << red << " " << green;
    ppmfile << " " << blue << "  ";
}
