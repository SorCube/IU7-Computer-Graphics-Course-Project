#include "objecttransformator.h"
#include "../model/model.h"
#include "../scene/camera.h"

void ModelTransformator::transform(std::shared_ptr<Object> obj)
{
    double x = tr.get_x();
    double y = tr.get_y();
    double z = tr.get_z();

    std::shared_ptr<Model> model = std::static_pointer_cast<Model>(obj);

    if (tr.is_shifting())
        model->shift(x, y, z);
    if (tr.is_scaling())
        model->scale(x, y, z);
    if (tr.is_rotation())
        model->rotate(x, y, z);
}

void CameraTransformator::transform(std::shared_ptr<Object> obj)
{
	double x = tr.get_x();
    double y = tr.get_y();
    double z = tr.get_z();

    std::shared_ptr<Camera> camera = std::static_pointer_cast<Camera>(obj);

    if (tr.is_shifting())
        camera->shift(x, y, z);
    if (tr.is_scaling())
        camera->scale(x, y, z);
    if (tr.is_rotation())
        camera->rotate(x, y, z);
}
