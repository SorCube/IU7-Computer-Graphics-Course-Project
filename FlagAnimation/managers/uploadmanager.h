#ifndef UPLOADMANAGER_H
#define UPLOADMANAGER_H

#include "../workers/modeluploader.h"

class UploadManager
{
public:
    UploadManager() = default;
    ~UploadManager() = default;
    
    std::shared_ptr<Model> upload_model(BaseUploader& upld, BaseBuilder& bld)
    {
        upld.open_src();
        std::shared_ptr<Model> model(upld.upload_model(bld));
        upld.close_src();
        return model;
    }
};

#endif // UPLOADMANAGER_H
