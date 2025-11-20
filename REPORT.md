Tower Defense CLI – Technical Report

Take-Home Assessment Submission
Author: Andres Palma

1. Introduction

This report documents the work completed for the C++ Tower Defense CLI take-home assessment.
The task involved implementing and improving functionality in three core engine classes:

Pooler (enemy memory pooling)

Tower (target acquisition and firing)

Logger (thread-safe asynchronous logging)

Additionally, I performed code cleanup, clarified logic paths, enforced consistency, and improved safety across the codebase.

I used GitHub Codespaces for compiling and running the game and leveraged GitHub Copilot selectively as an environment/setup assistant and for lightweight profiling help. All core logic, architecture, and implementation decisions were done manually.

2. Class API Overview: Expected Arguments & Return Values

Below is a concise summary of what the assignment required each class/method to accept/return.

2.1 Pooler Class
Method	Arguments	Returns	Purpose
Pooler(size_t minimumPoolSize)	minimum # of enemies to allocate	—	Constructor initializes the pool.
Enemy* SpawnEnemy(const Vector2D& spawnPosition)	spawn position for new enemy	pointer to active Enemy	Fetch or create an inactive enemy, activate it, and return pointer.
void DespawnEnemy(Enemy* enemy)	pointer to Enemy to deactivate	—	Deactivates enemy and returns it to the free list.
std::vector<Enemy*> GetActiveEnemies() const	—	vector of active Enemy pointers	Returns all active enemies for game updates/rendering.
void Clear()	—	—	Resets pool by deactivating all enemies.
size_t PoolSize()	—	number of allocated Enemy objects	Useful for debugging and tuning.
2.2 Tower Class
Method	Arguments	Returns	Purpose
Tower(int x, int y, int rateOfFire)	starting coordinates + fire rate	—	Constructor initializes tower state.
void Update(std::vector<Enemy*> enemies, std::vector<Bullet>& bullets)	enemy list + bullet list	—	Auto-fire behavior triggered every frame.
void ManualFire(std::vector<Enemy*> enemies, std::vector<Bullet>& bullets)	enemy list + bullet list	—	Fires bullet manually when autofire is off.
bool GetAutoFire() const	—	bool	Returns current autofire state.
void SetAutoFire(bool autoFire)	boolean toggle	—	Changes autofire mode.
int CalculateDistance(const Vector2D& a, const Vector2D& b) const	two positions	Manhattan distance	Distance metric used for target selection.
Enemy* FindClosestEnemy(const std::vector<Enemy*>& enemies) const	list of enemies	pointer to closest active Enemy	Manhattan-based nearest target acquisition.
2.3 Logger Class
Method	Arguments	Return	Purpose
void Log(const std::string& message)	message string	—	Pushes timestamped message into thread-safe queue.
void Flush()	—	—	Blocks until queue has been fully written to disk.
static Logger& GetInstance()	—	singleton instance	Provides global access to logger.
~Logger()	—	—	Ensures graceful thread shutdown and final flush.
3. Summary of Problems Found in Original Code

Upon inspection, several issues were identified:

3.1 General Codebase Issues

Large sections of commented-out legacy code.

Inconsistent logic (range checks, activation flags, ROF timing).

Missing header includes or unused includes.

Some unsafe patterns (e.g., logging without synchronization).

Poor separation of responsibilities in certain methods.

Lack of thread safety in logging.

Inconsistent use of const correctness.

3.2 Pooler Issues

The original pool stored enemies by value and tracked usage with std::vector<bool>.

No free list → inefficient linear scanning on every spawn.

Expanding pool required parallel inUse bookkeeping.

No clear separation between "allocated" and "active" enemies.

3.3 Tower Issues

FindClosestEnemy and CalculateDistance were not implemented.

Distance metric not defined (should be Manhattan).

Auto-fire logic merged with manual-fire path.

Range and cooldown checks were inconsistent.

Potential null pointer dereference if no enemy existed.

3.4 Logger Issues

Entire logging system was not thread-safe.

Queue drained with busy waiting (sleep_for(1000ms)).

No conditional variable → wasted CPU and inconsistent flushing.

Log order could invert because of push_back/pop_back misuse.

4. Implemented Solutions & Improvements
4.1 Memory Pool (Pooler)

Major changes:

Replaced raw vector of Enemy with std::unique_ptr<Enemy> for safer ownership.

Implemented a free list (std::vector<Enemy*>) to track unused enemies.

SpawnEnemy:

Pops from free list if available.

Expands pool only when necessary.

Activates enemy with supplied spawn position.

DespawnEnemy:

Deactivates enemy.

Pushes pointer back into free list.

Clear:

Deactivates all enemies and resets free list.

No dynamic allocations during gameplay, only during pool expansion.

Benefits:

O(1) spawn/return operations.

No repeated allocation/deallocation → more performant & predictable.

Safe ownership model, no raw deletes.

4.2 Tower Targeting & Firing Logic

Implemented:

Manhattan distance function:

𝑑
=
∣
𝑎
𝑥
−
𝑏
𝑥
∣
+
∣
𝑎
𝑦
−
𝑏
𝑦
∣
d=∣a
x
	​

−b
x
	​

∣+∣a
y
	​

−b
y
	​

∣

Ideal for grid-based movement.

FindClosestEnemy:

Iterates over active enemies.

Chooses smallest Manhattan distance.

Skips null or inactive enemies.

Unified firing logic:

Cooldown enforcement via steady_clock.

Range check using ENEMYRANGE.

Fire direction derived from grid difference.

Logging added for shot events and autofire toggles.

Improved code safety:

Prevented null dereferences.

Manual fire merges with auto-fire logic but bypasses autofire gate.

Clearer separation of responsibilities:

Update() → auto-fire loop.

ManualFire() → human input.

FireAtEnemy() → unified targeting.

FireBulletAtEnemy() → shot construction.

4.3 Logger – Thread-Safe Asynchronous Logging

Issue: original version was not thread-safe and wasted CPU cycles.

Implemented:

std::mutex + std::condition_variable for synchronization.

FIFO logging with std::queue<std::string>.

Dedicated logging thread calling ProcessLogs():

Sleeps until new messages arrive.

Writes in order, no inversion.

Added timestamp formatting:
"YYYY-MM-DD HH:MM:SS Message"

Clean shutdown:

exitFlag signals thread exit.

Flush() waits until queue is empty.

Benefits:

No race conditions.

Leak-free, safe destruction.

Logs generated in deterministic order.

File I/O no longer blocks gameplay.

5. General Code Quality Improvements

Across the three classes:

Removed large commented-out blocks and legacy code.

Standardized comment formatting and structure.

Improved naming consistency.

Removed unused headers & includes.

Added guard clauses to avoid undefined behavior.

Improved const-correctness in Tower methods.

Ensured Pooler & Tower return early on invalid input rather than dereferencing null.

Simplified logic paths for readability.

Ensured bullet spawning is deterministic and grid-accurate.

6. Environment, Debugging & Profiling Notes

I used:

GitHub Codespaces

Fast CMake builds

Easy to run terminal-based applications

Clean environment matching assignment requirements

Pre-installed compilers (gcc 13) enabled C++17 cleanly

GitHub Copilot

Used selectively for:

Boilerplate CMake adjustment guidance

Profiling and debugging suggestions

Faster navigation through large code blocks

Environment setup (initial build commands)

Copilot was not used for algorithm design or core logic — only as a development helper.

7. Recommendations for Future Improvements

The game engine works well, but several enhancements could improve maintainability and extendability:

7.1 Game Architecture

Introduce an ECS (Entity Component System) for scalability.

Use smart pointers consistently across entire project.

Introduce interfaces for renderable/game objects.

7.2 Pooler

Consider adding configurable growth strategies (e.g., double-size expansion).

Add instrumentation (stats: number of spawns, reuse rate).

7.3 Tower

Add proper range visualization for debugging.

Add configurable targeting logic (nearest, strongest, weakest, random).

7.4 Logger

Allow async file rotation when logs exceed size limits.

Add log levels (INFO, DEBUG, WARNING, ERROR).

7.5 Terminal Engine

Rendering has flicker/ghost artifacts:

Consider using ncurses or a framebuffer approach.

Bullet movement could be smoother with interpolation.

8. Conclusion

The Tower Defense CLI now has:

A safe and efficient memory pool,

A working Manhattan-distance targeting system,

A thread-safe logger,

Cleaned and modernized code following C++17 standards,

Improved readability, maintainability, and correctness.

All required features are complete, fully implemented, and tested.
