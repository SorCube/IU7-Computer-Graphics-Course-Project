#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "../workers/objecttransformator.h"
#include "../exceptions/transformexception.h"
#include "../model/model.h"
#include "../scene/camera.h"

class ModelManager
{
public:
    ModelManager() = default;
    ~ModelManager() = default;

    void transform(BaseTransformator& tr, const ModelIter& b,
				   const ModelIter& e)
    {
        for (ModelIter iter = b; iter != e; ++iter)
        {
            if (!(*iter))
                throw NoObjectToTranformException();

            tr.transform(std::static_pointer_cast<Object>(*iter));
        }
    }
};

class CameraManager
{
public:
    CameraManager() = default;
    ~CameraManager() = default;

    void transform(BaseTransformator& tr, const CameraIter& b,
				   const CameraIter& e)
    {
        for (CameraIter iter = b; iter != e; ++iter)
        {
            if (!(*iter))
                throw NoObjectToTranformException();

            tr.transform(std::static_pointer_cast<Object>(*iter));
        }
    }
};

#endif // OBJECTMANAGER_H
