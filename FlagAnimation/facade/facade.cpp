#include "facade.h"

void Facade::add_model(BaseUploader& upld, BaseBuilder& bld)
{
	scene.add_model(upload_manager.upload_model(upld, bld));
}

void Facade::add_model(Model model)
{
	scene.add_model(std::make_shared<Model>(model));
}

void Facade::remove_model(size_t index)
{
	scene.remove_model(index);
}

void Facade::add_camera(Vertex pos)
{
	Camera* camera_ptr = new Camera(pos);
    std::shared_ptr<Camera> camera(camera_ptr);
    scene.add_camera(camera);
}

void Facade::remove_camera(size_t index)
{
    scene.remove_camera(index);
}

void Facade::transform_model(BaseTransformator& tr, ssize_t index)
{
    ModelIter begin = (index == -1) ? scene.model_begin() :
									  scene.model_index(index);
    ModelIter end = (index == -1) ? scene.model_end() :
									scene.model_index(index + 1);
    model_manager.transform(tr, begin, end);
}

void Facade::transform_camera(BaseTransformator &tr, size_t index)
{
    CameraIter begin = scene.camera_index(index);
    CameraIter end = scene.camera_index(index + 1);
    camera_manager.transform(tr, begin, end);
}

void Facade::draw(BaseDrawer& drw, size_t camera_index)
{
    ModelIter begin = scene.model_begin();
    ModelIter end = scene.model_end();
    draw_manager.draw_model(drw, begin, end, *(scene.get_camera(camera_index)));
}
