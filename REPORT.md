# Tower Defense CLI – Technical Report
Take-Home Assessment Submission

## 1. Introduction

This report documents the work completed for the C++ Tower Defense CLI take-home assessment.
The task involved implementing and improving functionality in three core engine classes:

- Pooler (enemy memory pooling)
- Tower (target acquisition and firing)
- Logger (thread-safe asynchronous logging)
  
Additionally, I performed code cleanup, clarified logic paths, enforced consistency, and improved safety across the codebase.
I used GitHub Codespaces for compiling and running the game and leveraged GitHub Copilot selectively as an environment/setup assistant and for lightweight
profiling help. All core logic, architecture, and implementation decisions were done manually.

## 2. Overview of Required Class Responsibilities

### Pooler 

- Manages reusable Enemy objects to avoid frequent heap allocation.
- Must provide: SpawnEnemy(), DespawnEnemy(), GetActiveEnemies(), Clear(), and PoolSize().

### Tower 

- Identifies and fires at the closest enemy using Manhattan distance.
- Must implement: CalculateDistance(), FindClosestEnemy(), and respect fire rate and range.

### Logger

- Asynchronous, thread-safe logging of messages with timestamps.
- Must implement: Log() and Flush() while ensuring ordered, safe shutdown.

## 3. Class API Overview: Expected Arguments & Return Values

Below is a concise summary of what the assignment required each class/method to accept/return.

### 3.1 Pooler Class

| Method                                             | Arguments                        | Returns                           | Purpose                                                             |
| -------------------------------------------------- | -------------------------------- | --------------------------------- | ------------------------------------------------------------------- |
| `Pooler(size_t minimumPoolSize)`                   | minimum # of enemies to allocate | —                                 | Constructor initializes the pool.                                   |
| `Enemy* SpawnEnemy(const Vector2D& spawnPosition)` | spawn position for new enemy     | pointer to active Enemy           | Fetch or create an inactive enemy, activate it, and return pointer. |
| `void DespawnEnemy(Enemy* enemy)`                  | pointer to Enemy to deactivate   | —                                 | Deactivates enemy and returns it to the free list.                  |
| `std::vector<Enemy*> GetActiveEnemies() const`     | —                                | vector of active Enemy pointers   | Returns all active enemies for game updates/rendering.              |
| `void Clear()`                                     | —                                | —                                 | Resets pool by deactivating all enemies.                            |
| `size_t PoolSize()`                                | —                                | number of allocated Enemy objects | Useful for debugging and tuning.                                    |

### 3.2 Tower Class

| Method                                                                       | Arguments                        | Returns                         | Purpose                                     |
| ---------------------------------------------------------------------------- | -------------------------------- | ------------------------------- | ------------------------------------------- |
| `Tower(int x, int y, int rateOfFire)`                                        | starting coordinates + fire rate | —                               | Constructor initializes tower state.        |
| `void Update(std::vector<Enemy*> enemies, std::vector<Bullet>& bullets)`     | enemy list + bullet list         | —                               | Auto-fire behavior triggered every frame.   |
| `void ManualFire(std::vector<Enemy*> enemies, std::vector<Bullet>& bullets)` | enemy list + bullet list         | —                               | Fires bullet manually when autofire is off. |
| `bool GetAutoFire() const`                                                   | —                                | bool                            | Returns current autofire state.             |
| `void SetAutoFire(bool autoFire)`                                            | boolean toggle                   | —                               | Changes autofire mode.                      |
| `int CalculateDistance(const Vector2D& a, const Vector2D& b) const`          | two positions                    | Manhattan distance              | Distance metric used for target selection.  |
| `Enemy* FindClosestEnemy(const std::vector<Enemy*>& enemies) const`          | list of enemies                  | pointer to closest active Enemy | Manhattan-based nearest target acquisition. |

### 3.3 Logger Class

| Method                                 | Arguments      | Return             | Purpose                                            |
| -------------------------------------- | -------------- | ------------------ | -------------------------------------------------- |
| `void Log(const std::string& message)` | message string | —                  | Pushes timestamped message into thread-safe queue. |
| `void Flush()`                         | —              | —                  | Blocks until queue has been fully written to disk. |
| `static Logger& GetInstance()`         | —              | singleton instance | Provides global access to logger.                  |
| `~Logger()`                            | —              | —                  | Ensures graceful thread shutdown and final flush.  |


## 4. Summary of Problems Found in Original Code

Upon inspection, several issues were identified:

### 4.1 Pooler Issues

- Relied on parallel vectors (pool + inUse) and linear scanning.
- No true free list → inefficient spawning.
- Ownership and deletion risks due to raw memory patterns.

### 4.2 Tower Issues

- Missing distance calculation and target selection logic.
- Range and cooldown logic are inconsistent.
- Auto-fire and manual-fire intertwined without proper checks.

#### 4.3 Logger Issues

- Not thread-safe.
- Used busy waiting (sleep_for loops).
- Could write logs out of order.
- Shutdown was not synchronized.

## 5. Implemented Solutions & Improvements

### 5.1 Memory Pool (Pooler)

- Replaced enemy storage with std::unique_ptr<Enemy> for safe ownership.
- Implemented a free list (std::vector<Enemy*>) for O(1) spawn/despawn.
- Ensured the pool always maintains a minimum size.
- Spawning now:
-- Pulls from free list if possible.
-- Grows pool only when required.
- Clearing the pool deactivates all enemies and resets free list.

Result: Higher performance, no unnecessary allocations, and safer memory management

### 5.2 Tower Targeting & Firing Logic

- Implemented Manhattan distance for grid-appropriate targeting.
- Added a clear FindClosestEnemy() using distance comparisons.
- Unified firing logic with proper checks:
  - Auto-fire respects rate of fire AND range.
  - Manual fire ignores autofire toggle but still respects cooldown.
- Added direction-based bullet spawning.
- Added logging hooks for debugging (auto-fire state, firing events).

Result: Correct enemy selection, predictable firing behavior, and cleaner gameplay logic.

### 5.3 Logger – Thread-Safe Asynchronous Logging

- Implemented a mutex + condition_variable protected queue.
- Added worker thread consuming log entries in FIFO order.
- Added clean shutdown with exitFlag and Flush().
- Improved timestamp formatting (YYYY-MM-DD HH:MM:SS).
- Ensured minimal blocking and no busy waiting.

Result: Correctly ordered log output, safe concurrent usage, and efficient I/O.

## 6. General Code Quality Improvements

- Removed outdated commented code blocks.
- Simplified and clarified method logic and responsibilities.
- Reduced unnecessary includes.
- Improved const-correctness and early-return safety checks.
- Standardized naming, comments, and spacing across classes.

## 7. Recommendations for Future Improvements

- Adopt an ECS-based architecture for scalability.
- Replace manual terminal rendering with a proper rendering library (ncurses or similar).
- Add log levels and file rotation to Logger.
- Clean up the grid code so that there are no holes in the grid.
- Improve the Message Display so that all letters of the message are replaced at once.
- Provide visual debugging for tower range and bullet paths.
- Add performance metrics (e.g., pool reuse rate).

## 8. Conclusion

The take-home implementation now includes:

- A robust, efficient enemy memory pool
- A correct Manhattan-distance targeting system
- A thread-safe, asynchronous logger
- Cleaned and modernized code compliant with C++17

The game runs smoothly, and all required features are fully implemented and tested.
