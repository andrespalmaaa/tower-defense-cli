//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include "game.h"

// Platform-specific input handler
#ifdef _WIN32
#include "input_handler_windows.h"
#else
#include "input_handler_unix.h"
#endif
#include "logger.h"
#include "screen.h"

int main() {
    Logger& logger = Logger::GetInstance();

    logger.Log("Starting game...");

    srand(static_cast<unsigned>(time(0)));

    Game game(GRID_WIDTH, GRID_HEIGHT);

    int wave = 1;

    while (!game.IsGameOver()) {
        auto lastUpdateTime =
            std::chrono::steady_clock::now() - std::chrono::milliseconds(FRAME_DURATION);

        auto lastSpawnTime =
            std::chrono::steady_clock::now() - std::chrono::seconds(ENEMYSPAWNINTERVAL);

        int totalEnemiesToSpawn = wave * ENEMYSPAWNBULKSIZE;

        game.Reset();
        game.SpawnTower();

        do {
            auto currentTime = std::chrono::steady_clock::now();

            if (totalEnemiesToSpawn > 0 && currentTime - lastSpawnTime >= ENEMYSPAWNINTERVAL) {
                game.SpawnEnemies(ENEMYSPAWNBULKSIZE);
                totalEnemiesToSpawn -= ENEMYSPAWNBULKSIZE;
                lastSpawnTime = currentTime;

                logger.Log("Spawned " + std::to_string(ENEMYSPAWNBULKSIZE) + " enemies");
            }

            if (currentTime - lastUpdateTime >= FRAME_DURATION) {
                game.displayMessage = "Wave " + std::to_string(wave);

                if (game.HasEnemyReachedTower()) {
                    game.displayMessage = "Game Over! An enemy has reached the tower.";
                    game.SetGameOver(true);
                }

                game.Update();
                game.Render();
                lastUpdateTime = currentTime;
            }

            InputEvent event = getKeyPress();
            switch (event) {
                case InputEvent::KEY_A: {
                    game.tower.SetAutoFire(!game.tower.GetAutoFire());
                    break;
                }
                case InputEvent::SPACE:
                    if (!game.tower.GetAutoFire()) {
                        game.FireAtEnemy();
                    }
                    break;
                case InputEvent::ESCAPE:
                    game.SetGameOver(true);
                    break;
                default:
                    break;
            }
            // Small sleep to reduce CPU usage
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while((game.ActiveEnemiesCount() > 0 || totalEnemiesToSpawn > 0) && !game.IsGameOver());

        if (!game.IsGameOver()) {
            wave++;
            game.tower.SetAutoFire(true);
            game.displayMessage = "New wave coming...";
            game.Render();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        logger.Log(game.displayMessage);
    }

    Screen::MoveCursorToEnd();

    logger.Log("Exiting game...");

    // Ensure all logs are written before exiting
    logger.Flush();

    return 0;
}
