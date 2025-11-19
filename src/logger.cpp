//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "logger.h"

#include <iomanip>
#include <iostream>
#include <thread>

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : logFile("log.txt", std::ios_base::trunc) {
    logThread = std::thread(&Logger::ProcessLogs, this);
}

Logger::~Logger() {
    {
        exitFlag = true;
    }
    if (logThread.joinable()) {
        logThread.join();
    }

}

void Logger::ProcessLogs() {
    while (true) {
        while (!logQueue.empty()) {
            logFile << logQueue.back() << std::endl;
            logQueue.pop_back();
        }

        if (exitFlag) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

std::string Logger::GetCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}
