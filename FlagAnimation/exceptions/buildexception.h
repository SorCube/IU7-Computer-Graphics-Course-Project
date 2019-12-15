#ifndef BUILDEXCEPTION_H
#define BUILDEXCEPTION_H

#include "baseexception.h"

class NoObjectToBuildException : public BaseException
{
private:
    static constexpr const char* error_msg = "Error: no object to build";
public:
    explicit NoObjectToBuildException() : BaseException(error_msg) {}
    explicit NoObjectToBuildException(const std::string& message) :
        BaseException(error_msg + message) {}
};

#endif // BUILDEXCEPTION_H
