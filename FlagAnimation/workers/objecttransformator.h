#ifndef OBJECTTRANSFORMATOR_H
#define OBJECTTRANSFORMATOR_H

#include <memory>

#include "../transformation/transformation.h"
#include "../model/object.h"

class BaseTransformator
{
public:
    BaseTransformator() = default;
    virtual ~BaseTransformator() = default;

    virtual void transform(std::shared_ptr<Object> obj) = 0;
};

class ModelTransformator : public BaseTransformator
{
public:
    ModelTransformator(BaseTransformation& tr) : tr(tr) {}
    ~ModelTransformator() = default;

    void transform(std::shared_ptr<Object> obj);

private:
    BaseTransformation& tr;
};

class CameraTransformator : public BaseTransformator
{
public:
    CameraTransformator(BaseTransformation& tr) : tr(tr) {}
    ~CameraTransformator() = default;

    void transform(std::shared_ptr<Object> obj);

private:
    BaseTransformation& tr;
};

#endif // OBJECTTRANSFORMATOR_H
