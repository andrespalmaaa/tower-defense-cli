//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef POOLER_H
#define POOLER_H

#include <memory>
#include <list>

#include "enemy.h"

// Implement the following methods:
// Clear()
// SpawnEnemy()
// DespawnEnemy()
// GetActiveEnemies()

class Pooler {
   public:
    Pooler(size_t minimumPoolSize);
    size_t PoolSize();

   private:
    std::list<Enemy*> enemies;
    size_t minimumPoolSize;

    Enemy* CreateEnemy();
};

#endif  // POOLER_H