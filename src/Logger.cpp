//
// Created by Daniel on 11/10/2020.
//

#include "Logger.h"
#include <iostream>
#include <fstream>

static std::optional<std::string> loggerFile;

void Logger::appendMessage(const std::string& message) {
    if (loggerFile) {
        std::ofstream file(loggerFile.value(), std::ios_base::app);
        std::string data(message+"\n");
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
