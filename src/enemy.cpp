//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "enemy.h"

#include <cmath>

#include "constants.h"

Enemy::Enemy() : position({0, 0}), target({0, 0}), velocity(0.0), frameCounter(0), active(false) {}

void Enemy::Activate(const Vector2D& spawnPosition) {
    position = spawnPosition;
    active = true;
}

void Enemy::Deactivate() { active = false; }

bool Enemy::IsActive() const { return active; }

// Setters
void Enemy::SetPosition(Vector2D position) { this->position = position; }
void Enemy::SetTarget(Vector2D target) { this->target = target; }

void Enemy::SetVelocity(double velocity) { this->velocity = velocity; }

// Getters
Vector2D Enemy::GetPosition() const { return position; }
Vector2D Enemy::GetTarget() const { return target; }

double Enemy::GetVelocity() const { return velocity; }

// Update method
void Enemy::Update() {
    frameCounter++;

    // Determine how often the enemy should move based on velocity and frame rate
    if (frameCounter >= (FRAMERATE / velocity)) {
        position = CalculateNewPosition();

        // Reset frame counter
        frameCounter = 0;
    }
}

// calculate new position
Vector2D Enemy::CalculateNewPosition() {
    Vector2D newPosition = position;

    if (newPosition.x < target.x)
        newPosition.x += 1;
    else if (newPosition.x > target.x)
        newPosition.x -= 1;

    if (newPosition.y < target.y)
        newPosition.y += 1;
    else if (newPosition.y > target.y)
        newPosition.y -= 1;

    return newPosition;
}
