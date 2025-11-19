//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "grid_cell.h"

GridCell::GridCell(const Vector2D &position, const Texture &texture)
    : position(position), texture(texture) {}

const Texture &GridCell::GetTexture() const {
    return texture;
}

void GridCell::SetTexture(const Texture &texture) {
    this->texture = texture;
}

const Vector2D &GridCell::GetPosition() const {
    return position;
}
