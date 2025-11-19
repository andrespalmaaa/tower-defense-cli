//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "color.h"
#include "vector2d.h"
#include "texture.h"

// A class to represent an explosion on the game grid.
//
// This class is used to manage the visual representation of an explosion on the
// game grid. It handles the updating of the explosion's state and the rendering
// of the explosion on the grid.
class Explosion {
   public:
    Vector2D position;
    int framesRemaining;
    Texture texture;

    explicit Explosion(Vector2D position, Color color = Color::YELLOW);

    void Update();
    bool IsFinished() const;
};

#endif // EXPLOSION_H