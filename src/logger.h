//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <vector>
#include <string>
#include <thread>

// Implement the following methods:
// Log
// Flush
// Message format is "2024-08-30 14:48:16 Starting game..."

class Logger {
   public:
    static Logger& GetInstance();

    ~Logger();

   private:
    Logger();

    std::ofstream logFile;
    std::thread logThread;
    std::vector<std::string> logQueue;
    bool exitFlag = false;

    void ProcessLogs();
    std::string GetCurrentTimestamp();
};

#endif  // LOGGER_H
