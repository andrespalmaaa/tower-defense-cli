//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "grid.h"

#include <iostream>

#include "vector2d.h"

Grid::Grid(int w, int h) : width(w), height(h), grid(h) {
    for (int i = 0; i < height; ++i) {
        grid[i].reserve(width);
        for (int j = 0; j < width; ++j) {
            grid[i].emplace_back(Vector2D(j, i));
        }
    }
}


void Grid::ClearTextureBuffer() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            grid[i][j].SetTexture(Texture('*', Color::RESET));
        }
    }
}

void Grid::DrawToGrid(const GridCell &cell) {
    const Vector2D &pos = cell.GetPosition();
    grid[pos.y][pos.x] = cell;
}

std::vector<std::vector<GridCell>> &Grid::GetData() { return grid; }

GridCell &Grid::GetDataAt(const Vector2D &pos) { return grid[pos.y][pos.x]; }

void Grid::Render() {
    std::cout << "\033[2J";  // Clear the screen
    std::cout << "\033[H";   // Move the cursor to the top-left corner

    // Render the grid with colors
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Texture cellTexture = grid[i][j].GetTexture();
            std::cout << cellTexture.GetRepresentation();
        }
        std::cout << std::endl;
    }

    std::cout.flush();
}
