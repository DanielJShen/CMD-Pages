//
// Created by Daniel on 11/10/2020.
//

#include "Logger.h"
#include <iostream>
#include <fstream>
#include <chrono>

static std::optional<std::string> loggerFile;

void Logger::appendMessage(const std::string& message) {
    if (loggerFile) {
        std::ofstream file(loggerFile.value(), std::ios_base::app);

        std::string data(getTime()+" | "+message+"\n");
        file << data;
        file.close();
    }
}

void Logger::initLogger(std::string filePath) {
    loggerFile = std::move(filePath);
    std::ofstream file(loggerFile.value());
    std::string data("## CMDPAGES START ##\n");
    file << data;
    file.close();
}

std::string Logger::getTime() {
    time_t currentTime = std::time(0);
    tm *localTime = std::localtime(&currentTime);
    std::string dayString = std::to_string(localTime->tm_mday);
    std::string monthString = std::to_string(1 + localTime->tm_mon);
    std::string yearString = std::to_string(1900 + localTime->tm_year);
    std::string hourString = std::to_string(localTime->tm_hour);
    std::string minString = std::to_string(localTime->tm_min);
    std::string secString = std::to_string(localTime->tm_sec);

    dayString = localTime->tm_mday < 10 ? "0"+dayString : dayString;
    monthString = localTime->tm_mon < 10 ? "0"+monthString : monthString;

    hourString = localTime->tm_hour < 10 ? "0"+hourString : hourString;
    minString = localTime->tm_min < 10 ? "0"+minString : minString;
    secString = localTime->tm_sec < 10 ? "0"+secString : secString;

    return dayString+"/"+monthString+"/"+yearString+" "+hourString+":"+minString+":"+secString;
}
