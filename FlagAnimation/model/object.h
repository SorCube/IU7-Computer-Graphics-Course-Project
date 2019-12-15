#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;

    virtual bool isVisible() = 0;
};

class VisibleObject : public Object
{
public:
    VisibleObject() = default;
    virtual ~VisibleObject() = default;

    bool isVisible() override { return true; }
};

class InvisibleObject : public Object
{
public:
    InvisibleObject() = default;
    virtual ~InvisibleObject() = default;

    bool isVisible() override { return false; }
};

typedef std::vector<std::shared_ptr<Object>>::iterator ObjIter;

#endif // OBJECT_H
