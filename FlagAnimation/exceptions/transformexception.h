#ifndef TRANSFORMEXCEPTION_H
#define TRANSFORMEXCEPTION_H

#include "baseexception.h"

class NoObjectToTranformException : public BaseException
{
private:
    static constexpr const char* error_msg =
			"Error: no object to tranform.";
public:
    explicit NoObjectToTranformException() : BaseException(error_msg) {}
    explicit NoObjectToTranformException(const std::string& message) : 
        BaseException(error_msg + message) {}
};

class NoVertexToTranformException : public BaseException
{
private:
    static constexpr const char* error_msg =
			"Error: no vertex to tranform.";
public:
    explicit NoVertexToTranformException() : BaseException(error_msg) {}
    explicit NoVertexToTranformException(const std::string& message) : 
        BaseException(error_msg + message) {}
};

#endif // TRANSFORMEXCEPTION_H
