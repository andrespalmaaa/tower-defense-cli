//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "bullet.h"

Bullet::Bullet(Vector2D startPos, Vector2D dir) : position(startPos), direction(dir) {}

Vector2D Bullet::GetPosition() const { return position; }

Vector2D Bullet::GetDirection() const { return direction; }

void Bullet::Update() {
    position.x += direction.x;
        position.y += direction.y;
}