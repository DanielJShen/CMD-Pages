//
// Created by Daniel on 11/10/2020.
//
#include <string>
#include <optional>

#ifndef CMDPAGES_LOGGER_H
#define CMDPAGES_LOGGER_H


class Logger {
public:
    static void appendMessage(const std::string& message);
    static void initLogger(std::string filePath);
private:
    static std::string getTime();
};


#endif //CMDPAGES_LOGGER_H
