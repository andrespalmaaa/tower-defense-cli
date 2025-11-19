//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef VECTOR2D_H
#define VECTOR2D_H

// A struct to represent a 2D vector.
//
// This struct is used to represent a 2D vector with two integer coordinates.
struct Vector2D {
    int x;
    int y;

    // Constructor
    Vector2D(int x = 0, int y = 0) : x(x), y(y) {}
};

#endif  // VECTOR2D_H