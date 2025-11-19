//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef ENEMY_H
#define ENEMY_H

#include "vector2d.h"
#include "texture.h"

// Enemy class
// A class to represent an enemy in the game.
// This class is used to manage the state of an enemy in the game.
// It handles the updating of the enemy's state and the rendering of the enemy on the grid.
class Enemy {
   public:
    Texture texture = Texture('@', Color::RED);

    Enemy();

    // Pooling methods
    void Activate(const Vector2D& startPosition);
    void Deactivate();
    bool IsActive() const;

    void SetPosition(Vector2D position);
    void SetTarget(Vector2D target);
    void SetVelocity(double velocity);
    Vector2D GetPosition() const;
    Vector2D GetTarget() const;
    double GetVelocity() const;

    void Update();

    Vector2D CalculateNewPosition();

   private:
    bool active;
    Vector2D position;
    Vector2D target;
    double velocity;
    int frameCounter;
};

#endif  // ENEMY_H