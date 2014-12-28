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
