#include "modelbuilder.h"
#include "../exceptions/buildexception.h"

std::shared_ptr<Model> ModelBuilder::get_model() const
{
    return model;
}

void ModelBuilder::build_model()
{
    model = std::make_shared<Model>();
}

void ModelBuilder::build_vertex(double x, double y, double z)
{
    if (!is_model_built())
        throw NoObjectToBuildException();

    Vertex v(x, y, z);
    model->get_vertices().push_back(v);
}

void ModelBuilder::build_triangle(size_t v1, size_t v2, size_t v3)
{
    if (!is_model_built())
        throw NoObjectToBuildException();

    Triangle tr(v1, v2, v3);
    model->get_triangles().push_back(tr);
}

bool ModelBuilder::is_model_built() const
{
    return (model != nullptr);
}
