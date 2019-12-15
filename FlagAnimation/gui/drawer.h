#ifndef DRAWER_H
#define DRAWER_H

#include "canvas.h"
#include "../model/model.h"
#include "../scene/camera.h"
#include "../model/mathvector.h"

class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

    virtual void draw_edge(Vertex v1, Vertex v2,
						   QColor colour = QColor(0, 0, 0)) = 0;
	
	virtual void draw_triangle(std::vector<Vertex> v, Vertex light_pos,
							   QColor colour, bool outline = false) = 0;
	
	virtual void draw_scene(std::vector<Model> models, Camera& cam) = 0;
	
};

class ModelDrawer : public BaseDrawer
{
public:
    ModelDrawer(Canvas* canv);
    ~ModelDrawer() = default;

    void draw_edge(Vertex v1, Vertex v2,
				   QColor colour = QColor(0, 0, 0)) override;
	
	void draw_triangle(std::vector<Vertex> v, Vertex light_pos,
					   QColor colour, bool outline = false) override;
	
	void draw_scene(std::vector<Model> models, Camera& cam) override;

private:
    Canvas* canvas;
	
	Vertex light;
	QColor FC, LC;
	
	int** z_buf;
	QColor** c_buf;
};

#endif // DRAWER_H
