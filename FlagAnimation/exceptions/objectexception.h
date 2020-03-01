#ifndef OBJECTEXCEPTION_H
#define OBJECTEXCEPTION_H

#include "baseexception.h"

class OutOfRangeObjectException : public BaseException
{
private:
    static constexpr const char* error_msg = "Error: object out of range";
public:
    explicit OutOfRangeObjectException() : BaseException(error_msg) {}
    explicit OutOfRangeObjectException(const std::string& message) :
        BaseException(error_msg + message) {}
};
#endif // OBJECTEXCEPTION_H
