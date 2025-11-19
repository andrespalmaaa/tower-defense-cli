//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef BULLET_H
#define BULLET_H

#include "color.h"
#include "constants.h"
#include "vector2d.h"
#include "texture.h"

// A class to represent a bullet in the game.
//
// This class is used to manage the state of a bullet in the game. It handles
// the updating of the bullet's state and the rendering of the bullet on the
// grid.
class Bullet {
   public:
    Texture texture = Texture('o', Color::BLUE);

    Bullet(Vector2D startPos, Vector2D dir);

    Vector2D GetPosition() const;
    Vector2D GetDirection() const;

    void Update();

   private:
    Vector2D position;
    Vector2D direction;
};

#endif  // BULLET_H