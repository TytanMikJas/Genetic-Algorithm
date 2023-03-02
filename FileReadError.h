#pragma once
#include <iostream>

class FileReadError : public std::exception
{
public:
    // Constructor
    FileReadError(const std::string& fileName, const std::string& errorMessage)
        : fileName(fileName), errorMessage(errorMessage) {}

    // Method that displays given error
    std::string displayError() {
        return fileName + errorMessage;
    }

private:
    std::string fileName;
    std::string errorMessage;
};