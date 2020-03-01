#ifndef MODELCREATOR_H
#define MODELCREATOR_H

#include <QColor>
#include "../model/model.h"

class ModelCreator
{
public:
	ModelCreator() = default;
	~ModelCreator() = default;
	
	Model create();
};

class PlateCreator : public ModelCreator
{
public:
	PlateCreator() = default;
	~PlateCreator() = default;
	
	Model create(Vertex center, double w, double h, QColor colour);
};

class FlexRectCreator : public ModelCreator
{
public:
	FlexRectCreator() = default;
	~FlexRectCreator() = default;
	
	Model create(Vertex center, double w, double h,
				 size_t grad_w, size_t grad_h, QColor colour);
};

class ParallelepipedCreator : public ModelCreator
{
public:
	ParallelepipedCreator() = default;
	~ParallelepipedCreator() = default;
	
	Model create(Vertex center, double a, double b, double c, QColor colour);
};

class CylinderCreator : public ModelCreator
{
public:
	CylinderCreator() = default;
	~CylinderCreator() = default;
	
	Model create(Vertex center, double rad, double height, size_t grad,
				 QColor colour);
};


/*class SphereCreator : public ModelCreator
{
	SphereCreator() = default;
	~SphereCreator() = default;
	
	Model create(Vertex center, double rad, double bottom=-1, double top=-1);
};


class ConeCreator : public ModelCreator
{
	ConeCreator() = default;
	~ConeCreator() = default;
	
	Model create(Vertex center, double rad, double height, int grad);
};


class RectCreator : public ModelCreator
{
	RectCreator() = default;
	~RectCreator() = default;
	
	Model create(Vertex top_left, Vertex bottom_right);
};*/


#endif // MODELCREATOR_H
