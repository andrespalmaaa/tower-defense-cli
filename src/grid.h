//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef GRID_H
#define GRID_H

#include <vector>

#include "grid_cell.h"
#include "texture.h"
#include "vector2d.h"

// A class to represent the game grid.
//
// This class is used to manage the state of the game grid. It handles
// the updating of the grid's state and the rendering of the grid on the console.
class Grid {
   public:
    Grid(int w, int h);

    void ClearTextureBuffer();
    void DrawToGrid(const GridCell &cell);  // Method to draw a cell to the grid
    void Render();

    std::vector<std::vector<GridCell>> &GetData();
    GridCell &GetDataAt(const Vector2D &pos);

   private:
    int width, height;
    std::vector<std::vector<GridCell>> grid;
};

#endif  // GRID_H
