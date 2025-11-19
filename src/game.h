//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "bullet.h"
#include "explosion.h"
#include "grid.h"
#include "pooler.h"
#include "texture.h"
#include "tower.h"

// A class to manage the game state and logic.
// This class is the main entry point for the game.
// It manages the game state and handles the game logic.
// It is responsible for updating the game state and
// rendering the game on the console.
class Game {
   public:
    int width, height;
    Grid grid;
    std::vector<std::vector<Texture>> prevGrid;
    Tower tower;
    std::vector<Bullet> bullets;
    std::vector<Explosion> explosions;

    std::string displayMessage;
    std::string prevMessage;
    Pooler enemyPool = Pooler(MINIMUMENEMYPOOLSIZE);

    Game(int w, int h);

    size_t ActiveEnemiesCount();
    void SpawnTower();
    void SpawnEnemies(int count);
    bool HasEnemyReachedTower();
    bool IsGameOver();
    void SetGameOver(bool isGameOver);

    void Update();
    void FireAtEnemy();
    void Render();
    void Reset();

   private:
    size_t activeEnemiesCount = 0;
    size_t prevActiveEnemiesCount = 0;
    size_t poolerUsage = 0;
    size_t prevPoolerUsage = 0;
    bool isGameOver = false;
    void CheckCollisions();
    void UpdateExplosions();
    void UpdateGrid();
};

#endif  // GAME_H
