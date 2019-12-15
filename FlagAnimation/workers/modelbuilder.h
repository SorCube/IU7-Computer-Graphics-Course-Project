#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include "../model/model.h"

class BaseBuilder
{
public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;

    virtual std::shared_ptr<Model> get_model() const = 0;
    virtual void build_model() = 0;
    virtual void build_vertex(double x, double y, double z) = 0;
    virtual void build_triangle(size_t v1, size_t v2, size_t v3) = 0;
};

class ModelBuilder : public BaseBuilder
{
public:
    ModelBuilder() : model(nullptr) {}
    ~ModelBuilder() = default;

    std::shared_ptr<Model> get_model() const;
    void build_model();
    void build_vertex(double x, double y, double z);
    void build_triangle(size_t v1, size_t v2, size_t v3);

protected:
    bool is_model_built() const;

protected:
    std::shared_ptr<Model> model;
};

#endif // MODELBUILDER_H
