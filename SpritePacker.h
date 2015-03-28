/*
This file is part of Sprite Packer

Copyright (c) 2014 Adam Romero

Sprite Packer is free software: you can redistribute
it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Sprite Packer is distributed in the hope that it will
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sprite Packer.  If not,
see <http://www.gnu.org/licenses/>.
*/

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
