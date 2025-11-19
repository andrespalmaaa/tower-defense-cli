//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "pooler.h"

#include <algorithm>

Pooler::Pooler(size_t minimumPoolSize) : minimumPoolSize(minimumPoolSize) {
}

size_t Pooler::PoolSize()
{
    return enemies.size();
}

Enemy* Pooler::CreateEnemy() {
    return new Enemy();
}
