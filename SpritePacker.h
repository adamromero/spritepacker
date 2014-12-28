#ifndef SPRITEPACKER_H
#define SPRITEPACKER_H

#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include "CImg.h"
#include "Cell.h"

struct SpritePacker {
   SpritePacker(const char *dir, const char *output)
      : directory(dir), outputFile(output) {}

   bool imageFilesFound();
   void outputMergedImage();
   void packImages();
   
private:
   std::string directory, outputFile;
   std::vector< cimg_library::CImg<unsigned char> > images;
   cimg_library::CImg<unsigned char> rectangle;
   std::vector<Cell> cells;
   
   void sortVectorByHeight();
   int largestImageWidth();
   void createCells(int idx, int x, int y, int height, int width);
   bool drawNextImage(cimg_library::CImg<unsigned char> image, int idx);
   bool imageInBounds(const Cell &cell, int height, int width);
   bool imageOverlaps(Cell &cell, int imgHeight, int imgWidth);
   bool overlap(const Point left1, const Point right1, const Point left2, const Point right2);
   
};

#endif
