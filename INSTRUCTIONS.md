# Instructions for Take Home Test
You will be adding features to a console-based tower defense game that is being developed using C++.
The game involves a tower defending against waves of enemies. The tower can automatically fire at enemies or shoot manually. The game features a grid-based representation of the game world where bullets, enemies, explosions, and the tower are displayed.

## Requirements

- A C++ compiler (e.g., g++, clang++)
- Standard C++ library (C++ 17)
- POSIX or Windows compatible environment for input handling

## Tasks

For this test, you will be working on managing the waves of the enemies, finding the closest enemy to the tower, and the saving the logs of the game to a file.
You will be editing only 3 classes: Pooler, Tower, and Logger. Each header class indicates which methods you must implement (you must interpret what arguments and return value is expected). Your tasks are as follows:

- Implement a **memory pool** for enemies in the ``Pooler`` class, respecting existing requirements (enforced by the class implementation), managing allocation/deallocation efficiently.
- Review and edit ``Tower`` class so that it finds closest enemy, calculating distance in a manner appropriate to the game logic.
- Review and edit ``Logger`` class so that it logs messages successfully (i.e. in order), with concurrency in mind.
- Review and update existing methods (from these 3 classes) to adjust to your solution.
- Review and update overall code in terms of **clarity, consistency and safety**. You can change the content of existing methods and create new auxiliary methods if needed.
- Write a **report** describing what you found, what you added and changed, and what other changes to the code you'd recommend (PDF or Markdown only).
- Feel free to use tools to analyse code (i.e. profiling tools). Add notes about this process in the report if you do.
- **Reminder: Please test for errors prior to submission.**


## Submission
Please submit back the files for the 3 classes and the report.
