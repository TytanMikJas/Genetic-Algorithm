#pragma once
#include <iostream>

class ConstructorError : public std::exception
{
public:
    // Constructor
    ConstructorError(const std::string& errorMessage)
        : errorMessage(errorMessage) {}

    // Method that displays given error
    std::string displayError() {
        return  errorMessage;
    }

private:
    std::string errorMessage;
};