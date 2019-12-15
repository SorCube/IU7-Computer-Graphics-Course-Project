#ifndef DRAWEXCEPTION_H
#define DRAWEXCEPTION_H

#include "baseexception.h"


class NoObjectToDrawException : public BaseException
{
private:
    static constexpr const char* error_msg = "Error: no object to draw";
public:
    explicit NoObjectToDrawException() : BaseException(error_msg) {}
    explicit NoObjectToDrawException(const std::string& message) :
        BaseException(error_msg + message) {}
};

class NoVertexToDrawException : public BaseException
{
private:
    static constexpr const char* error_msg = "Error: no vertex to draw";
public:
    explicit NoVertexToDrawException() : BaseException(error_msg) {}
    explicit NoVertexToDrawException(const std::string& message) :
        BaseException(error_msg + message) {}
};

class NoTriangleToDrawException : public BaseException
{
private:
    static constexpr const char* error_msg = "Error: no triangle to draw";
public:
    explicit NoTriangleToDrawException() : BaseException(error_msg) {}
    explicit NoTriangleToDrawException(const std::string& message) :
        BaseException(error_msg + message) {}
};

#endif // DRAWEXCEPTION_H
