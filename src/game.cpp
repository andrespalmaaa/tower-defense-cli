//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "game.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>

#include "screen.h"

namespace
{
    constexpr std::string_view ACTIVEENEMIESCOUNTTEXT("Active enemies: ");
    constexpr std::string_view POOLUSAGETEXT("Enemies pool usage: ");
}

Game::Game(int w, int h)
    : width(w),
      height(h),
      grid(w, h),
      tower(w / 2, h / 2, RATEOFFIRE),
      prevGrid(h, std::vector<Texture>(w, Texture('*', Color::RESET)))
      {}

void Game::SpawnTower() {
    int minDistance = 5;
    int maxX = width - minDistance - 1;
    int maxY = height - minDistance - 1;

    tower.position.x = minDistance + rand() % (maxX - minDistance + 1);
    tower.position.y = minDistance + rand() % (maxY - minDistance + 1);
}

void Game::SpawnEnemies(int count) {
    for (int i = 0; i < count; ++i) {
        int border = rand() % 4;
        int x = 0, y = 0;
        int velocity = rand() % ENEMYMAXSPEED + 1;

        switch (border) {
            case 0:  // Top border
                x = rand() % width;
                y = 0;
                break;
            case 1:  // Bottom border
                x = rand() % width;
                y = height - 1;
                break;
            case 2:  // Left border
                x = 0;
                y = rand() % height;
                break;
            case 3:  // Right border
                x = width - 1;
                y = rand() % height;
                break;
        }
        Enemy &enemy = *enemyPool.SpawnEnemy({x, y});

        enemy.SetTarget(tower.position);
        enemy.SetVelocity(velocity);
    }
}

void Game::CheckCollisions() {
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        if (bulletIt->GetPosition().x < 0 || bulletIt->GetPosition().x >= width ||
            bulletIt->GetPosition().y < 0 || bulletIt->GetPosition().y >= height) {
            bulletIt = bullets.erase(bulletIt);
            continue;
        }

        bool hit = false;

        // Get active enemies
        auto enemies = enemyPool.GetActiveEnemies();

        // use std::find_if to collect the enemies that are hit
        auto it = std::find_if(enemies.begin(), enemies.end(), [bulletIt](const auto &enemy) {
            return bulletIt->GetPosition().x == enemy->GetPosition().x &&
                   bulletIt->GetPosition().y == enemy->GetPosition().y;
        });

        if (it != enemies.end()) {
            Vector2D explosionPosition = (*it)->GetPosition();
            enemyPool.DespawnEnemy(*it);
            bulletIt = bullets.erase(bulletIt);
            explosions.emplace_back(explosionPosition);
            hit = true;
        }

        if (!hit) {
            ++bulletIt;
        }
    }
}

void Game::UpdateExplosions() {
    auto it = explosions.begin();
    while (it != explosions.end()) {
        it->Update();
        if (it->IsFinished()) {
            it = explosions.erase(it);
        } else {
            ++it;
        }
    }
}

bool Game::HasEnemyReachedTower() {
    for (auto enemy : enemyPool.GetActiveEnemies()) {
        if (enemy->GetPosition().x == tower.position.x &&
            enemy->GetPosition().y == tower.position.y) {
            enemyPool.DespawnEnemy(enemy);
            explosions.emplace_back(tower.position, Color::LIME);
            return true;
        }
    }

    return false;
}

size_t Game::ActiveEnemiesCount() { return activeEnemiesCount; }

bool Game::IsGameOver() { return isGameOver; }

void Game::SetGameOver(bool isGameOver) { isGameOver = isGameOver; }

void Game::UpdateGrid() {
    grid.ClearTextureBuffer();

    for (const auto &bullet : bullets) {
        GridCell cellBullet = GridCell(bullet.GetPosition(), bullet.texture);
        grid.DrawToGrid(cellBullet);
    }

    for (const auto enemy : enemyPool.GetActiveEnemies()) {
        GridCell cellEnemy = GridCell(enemy->GetPosition(), enemy->texture);
        grid.DrawToGrid(cellEnemy);
    }

    GridCell cellTower = GridCell(tower.position, tower.texture);
    grid.DrawToGrid(cellTower);

    for (const auto &explosion : explosions) {
        GridCell cellExplosion = GridCell(explosion.position, explosion.texture);
        grid.DrawToGrid(cellExplosion);
    }
}

void Game::Update() {
    const auto& activeEnemies = enemyPool.GetActiveEnemies();

    activeEnemiesCount = activeEnemies.size();

    for (auto enemy : activeEnemies) {
        GridCell newCell = grid.GetDataAt(enemy->CalculateNewPosition());
        Texture cellTexture = newCell.GetTexture();

        if (cellTexture.GetSymbol() == 'T' || cellTexture.GetSymbol() == '*') {
            enemy->Update();
        }
    }

    for (auto &bullet : bullets) {
        bullet.Update();
    }

    CheckCollisions();

    UpdateExplosions();
    UpdateGrid();

    if (tower.GetAutoFire()) {
        FireAtEnemy();
    }
}

void Game::FireAtEnemy() {
    if (tower.GetAutoFire()) {
        tower.Update(enemyPool.GetActiveEnemies(), bullets);
    } else {
        tower.ManualFire(enemyPool.GetActiveEnemies(), bullets);
    }
}

void Game::Render() {
    // Iterate over the grid and compare it with the previous state
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            GridCell currentCell = grid.GetData()[i][j];

            Texture currentCellTexture = currentCell.GetTexture();
            Texture prevCellTexture = prevGrid[i][j];

            if (currentCellTexture.GetSymbol() != prevCellTexture.GetSymbol()) {
                Screen::RenderText(j, i, currentCellTexture.GetRepresentation());
                prevGrid[i][j] = currentCellTexture;  // Update the previous grid
            }
        }
    }

    // Render autofire indicator
    if (tower.GetAutoFire()) {
        Screen::RenderText(width + 1, 0, "Auto-fire: ON ");
    } else {
        Screen::RenderText(width + 1, 0, "Auto-fire: OFF ");
    }

    // Render enemies count message
    if (prevActiveEnemiesCount != activeEnemiesCount) {
        // clear previous value
        Screen::RenderText(width + 1 + ACTIVEENEMIESCOUNTTEXT.size(), 2, "      ");
        Screen::RenderText(width + 1, 2, std::string(ACTIVEENEMIESCOUNTTEXT) + std::to_string(activeEnemiesCount) + " ");
    }

    // Render enemies pool usage bar
    poolerUsage = enemyPool.PoolSize();
    if (prevPoolerUsage != poolerUsage) {
        std::stringstream ss;

        // clear previous bar
        std::generate_n(
            std::ostream_iterator<std::string>(ss), prevPoolerUsage + 1, [](){ return " "; });
        Screen::RenderText(width + 22, 4, ss.str());
        ss.str(std::string()); // reset stream

        // generate new bar
        ss << '[';
        std::generate_n(std::ostream_iterator<std::string>(ss), poolerUsage, [](){ return "="; });
        ss << ']';

        Screen::RenderText(width + 1, 4, std::string(POOLUSAGETEXT) + ss.str());
        Screen::RenderText(width + 1 + POOLUSAGETEXT.size() + ENEMYSPAWNBULKSIZE / 2, 5, "^");

        prevPoolerUsage = poolerUsage;
    }

    // Update the message only if it has changed
    if (displayMessage != prevMessage) {
        int padding = (width - displayMessage.size()) / 2;
        Screen::RenderText(std::max(0, padding), height + 1, displayMessage);
        prevMessage = displayMessage;  // Update the previous message
    }

    std::cout.flush();
}

void Game::Reset() {
    grid.ClearTextureBuffer();
    grid.Render();
    enemyPool.Clear();
    bullets.clear();
    explosions.clear();

    poolerUsage = 0;
    prevPoolerUsage = 0;
}