#ifndef FACADE_H
#define FACADE_H

#include "../scene/scene.h"
#include "../managers/uploadmanager.h"
#include "../managers/drawmanager.h"
#include "../managers/objectmanager.h"


class Facade
{
public:
    Facade() = default;
    ~Facade() = default;

    void add_model(BaseUploader& upld, BaseBuilder& bld);
	void add_model(Model model);
	void add_model(std::shared_ptr<Model> model);
    void remove_model(size_t index);

    void add_camera(Vertex pos);
    void remove_camera(size_t index);

    void transform_model(BaseTransformator& tr, ssize_t index);
    void transform_camera(BaseTransformator& tr, size_t index);

    void draw(BaseDrawer& drw, size_t camera_index);

private:
    Scene scene;
    UploadManager upload_manager;
    DrawManager draw_manager;
    ModelManager model_manager;
    CameraManager camera_manager;
};

#endif // FACADE_H
