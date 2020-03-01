#ifndef SCENE_H
#define SCENE_H

#include "../model/model.h"
#include "camera.h"

#include <memory>
#include <vector>


class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    void add_model(const std::shared_ptr<Model>& model);
    void remove_model(ssize_t index);

    void add_camera(const std::shared_ptr<Camera>& camera);
    void remove_camera(size_t index);

    std::shared_ptr<Model> get_model(ssize_t index);
    std::shared_ptr<Camera> get_camera(size_t index);
	
	ModelIter model_begin();
	ModelIter model_end();
	
	CameraIter camera_begin();
    CameraIter camera_end();
	
    ModelIter model_index(ssize_t index);
    CameraIter camera_index(size_t index);

private:
	std::vector<std::shared_ptr<Model>> models;
	std::vector<std::shared_ptr<Camera>> cameras;
};

#endif // SCENE_H
