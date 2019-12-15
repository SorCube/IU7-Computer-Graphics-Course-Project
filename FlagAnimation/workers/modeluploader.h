#ifndef MODELUPLOADER_H
#define MODELUPLOADER_H

#include "../exceptions/uploadexception.h"
#include "modelbuilder.h"

#include <fstream>

class BaseUploader
{
public:
    BaseUploader() = default;
    virtual ~BaseUploader() = default;

    virtual std::shared_ptr<Model> upload_model(BaseBuilder& bld) = 0;
    virtual void open_src() = 0;
    virtual void close_src() = 0;
};

class ModelUploader : public BaseUploader
{
public:
    explicit ModelUploader(const std::string& name) : filename(name) {}
    ~ModelUploader() = default;

    std::shared_ptr<Model> upload_model(BaseBuilder &bld) override;

    void open_src() override;
    void close_src() override;

private:
    std::string filename;
    std::ifstream file;
};

#endif // MODELUPLOADER_H
