#ifndef DRAWER_H
#define DRAWER_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "canvas.h"
#include "model/model.h"
#include "scene/camera.h"
#include "model/mathvector.h"

struct BuffArgs
{
	QImage& img;
	size_t start;
	size_t end;
};

class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

    virtual void draw_edge(Vertex v1, Vertex v2,
						   QColor colour = QColor(0, 0, 0)) = 0;
	
	virtual void draw_triangle(std::vector<Vertex> v, std::vector<MathVector> n,
							   MathVector l, QColor colour,
							   bool outline = false) = 0;
	
	virtual void draw_scene(std::vector<Model> models, Camera& cam) = 0;
	
};

class ModelDrawer : public BaseDrawer
{
public:
    ModelDrawer(Canvas* canv);
    ~ModelDrawer() = default;

    void draw_edge(Vertex v1, Vertex v2,
				   QColor colour = QColor(0, 0, 0)) override;
	
	void draw_line(MathVector &A, MathVector &B, double ia, double ib,
				   QColor colour);
	
	void draw_triangle(std::vector<Vertex> v, std::vector<MathVector> n,
					   MathVector l, QColor colour,
					   bool outline = false) override;
	
	void draw_scene(std::vector<Model> models, Camera& cam) override;

private:
    Canvas* canvas;
	
	Vertex light;
	QColor FC, LC;
	
	int** z_buf;
	QColor** c_buf;
	
	std::vector<double> canv_shift = { IMG_SIZE / 2, IMG_SIZE / 2, 0 };
	std::vector<double> canv_rotate = { -M_PI / 4, M_PI / 5, -M_PI / 5.9 };
	Vertex canv_center = Vertex(IMG_SIZE / 2, IMG_SIZE / 2, 0);
	
	void fill_buffer(QImage& img, size_t start, size_t end);
};

#endif // DRAWER_H
