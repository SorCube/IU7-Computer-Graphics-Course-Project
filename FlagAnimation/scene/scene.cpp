#include "scene.h"
#include "../exceptions/objectexception.h"
#include "../model/model.h"

void Scene::add_model(const std::shared_ptr<Model>& model)
{
	models.push_back(model);
}

void Scene::remove_model(ssize_t index)
{
    if (index >= models.size() || index < -1)
        throw OutOfRangeObjectException("\nmethod: remove_model");
    else
        models.erase(models.begin() + index);
}

void Scene::add_camera(const std::shared_ptr<Camera>& camera)
{
	cameras.push_back(camera);
}

void Scene::remove_camera(size_t index)
{
	if (index >= cameras.size())
        throw OutOfRangeObjectException("\nmethod: remove_camera");
    else
        cameras.erase(cameras.begin() + index);
}

std::shared_ptr<Model> Scene::get_model(ssize_t index)
{
    if (index >= models.size() || index < -1)
        throw OutOfRangeObjectException("\nmethod: get_model");
    else
		return models[index];
}

std::shared_ptr<Camera> Scene::get_camera(size_t index)
{
    if (index >= cameras.size())
        throw OutOfRangeObjectException("\nmethod: get_camera");
    else
		return cameras[index];
}

ModelIter Scene::model_begin()
{
	return models.begin();
}

ModelIter Scene::model_end()
{
	return models.end();
}

CameraIter Scene::camera_begin()
{
	return cameras.end();
}

CameraIter Scene::camera_end()
{
	return cameras.end();
}

ModelIter Scene::model_index(ssize_t index)
{
	if (index == models.size())
        return models.end();

    if (index > models.size() || index < -1)
        throw OutOfRangeObjectException("\nmethod: model_index");
    else
        return models.begin() + index;
}

CameraIter Scene::camera_index(size_t index)
{
	if (index == cameras.size())
        return cameras.end();

    if (index > cameras.size())
        throw OutOfRangeObjectException("\nmethod: camera_index");
    else
        return cameras.begin() + index;
}
