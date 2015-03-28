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

#ifndef CELL_H
#define CELL_H

struct Cell {
	Cell(int h, int w, int x, int y) 
		: cellHeight(h), cellWidth(w), xCoordinate(x), yCoordinate(y) { occupied = false; }
		
	int height() const { return cellHeight; }
	int width() const { return cellWidth; }
	int x() const { return xCoordinate; }
	int y() const { return yCoordinate; }
	
	void resizeCell(int height, int width) { 
	   cellHeight = height;
	   cellWidth = width;
	}
	
	bool occupied;

private:
	int cellHeight;
	int cellWidth;
	int xCoordinate;
	int yCoordinate;
};

struct Point {
   int x, y;
};

#endif
