#ifndef UPLOADEXCEPTION_H
#define UPLOADEXCEPTION_H

#include "baseexception.h"

class OpenFileException : public BaseException
{
private:
    static constexpr const char* error_msg = "Error: opening file";
public:
    explicit OpenFileException() : BaseException(error_msg) {}
    explicit OpenFileException(const std::string& message) :
        BaseException(error_msg + message) {}
};

class CloseFileException : public BaseException
{
private:
    static constexpr const char* error_msg = "Error: closing file";
public:
    explicit CloseFileException() : BaseException(error_msg) {}
    explicit CloseFileException(const std::string& message) :
        BaseException(error_msg + message) {}
};

class ReadFileException : public BaseException
{
private:
    static constexpr const char* error_msg = "Error: reading file";
public:
    explicit ReadFileException() : BaseException(error_msg) {}
    explicit ReadFileException(const std::string& message) :
        BaseException(error_msg + message) {}
};

#endif // UPLOADEXCEPTION_H
