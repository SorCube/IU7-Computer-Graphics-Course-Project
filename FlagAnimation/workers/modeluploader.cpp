#include "modeluploader.h"

std::shared_ptr<Model> ModelUploader::upload_model(BaseBuilder& bld)
{
    try
    {
		size_t vertices_count, triangles_count, v1, v2, v3;
        bld.build_model();

        file >> triangles_count;

        for (size_t i = 0; i < triangles_count; ++i)
        {
            file >> v1 >> v2 >> v3;
            bld.build_triangle(v1, v2, v3);
        }

        double x, y, z;
        file >> vertices_count;

        for (size_t i = 0; i < vertices_count; ++i)
        {
            file >> x >> y >> z;
            bld.build_vertex(x, y, z);
        }
    }
    catch (const std::ifstream::failure& e)
    {
        throw ReadFileException();
    }

    return bld.get_model();
}

void ModelUploader::open_src()
{
    file.open(this->filename);
    if (!file)
        throw OpenFileException();
}

void ModelUploader::close_src()
{
    try
    {
        file.close();
    }
    catch (const std::ifstream::failure& e)
    {
        throw CloseFileException();
    }
}
