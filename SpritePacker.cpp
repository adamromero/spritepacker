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

#include "SpritePacker.h"
#include <algorithm>

void SpritePacker::createCells(int idx, int x, int y, int height, int width) {
   cells.push_back(Cell(images.at(idx).height(), 
   		width - (x + images.at(idx).width()), x + images.at(idx).width(), y));
   cells.push_back(Cell(height - images.at(idx).height(), 
   		images.at(idx).width(), x, y + images.at(idx).height()));		
}

bool SpritePacker::imageInBounds(const Cell &cell, int height, int width) {
   return (cell.x() + width <= rectangle.width() 
      && cell.y() + height <= rectangle.height());
}

bool SpritePacker::overlap(const Point left1, const Point right1, const Point left2, const Point right2) {
   if (left1.x >= right2.x || left2.x >= right1.x) {
      return false;
   }
   
   if (left1.y >= right2.y || left2.y >= right1.y) {
      return false;
   }
   
   return true;
}

bool SpritePacker::imageOverlaps(Cell &cell, int imgHeight, int imgWidth) {
   const Point left1 = {cell.x(), cell.y()};
   const Point right1 = {cell.x() + imgWidth, cell.y() + imgHeight};
   
   for (int i = 0; i < cells.size(); i++) {   
      const Point left2 = {cells.at(i).x(), cells.at(i).y()};
      const Point right2 = {cells.at(i).x() + cells.at(i).width(), cells.at(i).y() + cells.at(i).height()};
      
      if (overlap(left1, right1, left2, right2) && cells.at(i).occupied) {
         return true;
      } 
   }
   
   return false;
}

bool SpritePacker::drawNextImage(cimg_library::CImg<unsigned char> image, int idx) {
   for (int i = 0; i < cells.size(); i++) {
      if (imageInBounds(cells.at(i), image.height(), image.width()) && !cells.at(i).occupied) {
         if (!imageOverlaps(cells.at(i), image.height(), image.width())) {
            rectangle.draw_image(cells.at(i).x(), cells.at(i).y(), image, 1);
            const int cellHeight = cells.at(i).height();
            const int cellWidth = cells.at(i).width();
            cells.at(i).resizeCell(image.height(), image.width());
            createCells(idx, cells.at(i).x(), cells.at(i).y(), cellHeight, cellWidth); 
            cells.at(i).occupied = true;
            return true;
         }
      }
   }
   
   return false;
}

void SpritePacker::packImages() {
   sortVectorByHeight();
   rectangle.assign(largestImageWidth(), images.at(0).height(), 1, 3); 
   rectangle.draw_image(0, 0, images.at(0), 1); 
   createCells(0, 0, 0, rectangle.height(), rectangle.width());
   
   int i = 1;
   while (i < images.size()) {
   	  if (!drawNextImage(images.at(i), i)) {
   	  	 rectangle.resize(-130, -130, -100, -100, 0);
   	  } else {
   	     i++;
   	  }
   }
}

void SpritePacker::outputMergedImage() {
   outputFile += ".png";
   rectangle.save_png(outputFile.c_str());
}

bool SpritePacker::imageFilesFound() {
   const boost::filesystem::path filepath(directory);
   bool imageFound = false;

   boost::filesystem::directory_iterator iterator(filepath);
   for(; iterator != boost::filesystem::directory_iterator(); iterator++) {
      if (iterator->path().extension().string().compare(".jpg") == 0) {
         images.push_back(cimg_library::CImg<unsigned char>(iterator->path().c_str()));
         imageFound = true;
      }
   }

   return imageFound;
}

int SpritePacker::largestImageWidth() {
   int largestWidth = images.at(0).width();
   for (int i = 0; i < images.size(); i++) {
      for (int j = i + 1; j < images.size(); j++) {
         if (images.at(j).width() > largestWidth) {
            largestWidth = images.at(j).width();
         }
      }
   }

   return largestWidth;
}

void SpritePacker::sortVectorByHeight() {
	for (int i = 0; i < images.size(); i++) {
		for(int j = i + 1; j < images.size(); j++) {
			if (images.at(j).height() > images.at(i).height()) {
				iter_swap(images.begin() + i, images.begin() + j);
			}
		}
	}
}
