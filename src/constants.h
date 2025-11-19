//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <chrono>

static constexpr size_t GRID_WIDTH = 40;
static constexpr size_t GRID_HEIGHT = 20;
static constexpr size_t FRAMERATE = 10;
static constexpr std::chrono::milliseconds FRAME_DURATION(1000u / FRAMERATE);
static constexpr size_t RATEOFFIRE = 1 * (1000 / FRAMERATE);
static constexpr size_t ENEMYRANGE = 10;
static constexpr size_t MINIMUMENEMYPOOLSIZE = 5;
static constexpr size_t ENEMYSPAWNBULKSIZE = 10;
static constexpr size_t ENEMYMAXSPEED = 5;
static constexpr std::chrono::seconds ENEMYSPAWNINTERVAL(5);

#endif  // CONSTANTS_H
