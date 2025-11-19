//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "explosion.h"

Explosion::Explosion(Vector2D pos, Color color)
    : position(pos), framesRemaining(5), texture('X', color) {}

void Explosion::Update() {
    if (framesRemaining > 0) {
        framesRemaining--;
    }
}

bool Explosion::IsFinished() const {
    return framesRemaining <= 0;
}