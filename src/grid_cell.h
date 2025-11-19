//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef GRID_CELL_H
#define GRID_CELL_H

#include "texture.h"
#include "vector2d.h"

// A class to represent a single cell in the grid.
//
// This class encapsulates the texture and position information for a grid cell.
class GridCell {
   public:
    // Constructor to initialize the cell with a texture and position.
    GridCell(const Vector2D &position, const Texture &texture = Texture('*', Color::RESET));

    // Getter and Setter for the texture.
    const Texture &GetTexture() const;
    void SetTexture(const Texture &texture);

    // Getter for the position.
    const Vector2D &GetPosition() const;

   private:
    Texture texture;
    Vector2D position;
};

#endif  // GRID_CELL_H
