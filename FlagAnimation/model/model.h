#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "object.h"
#include "triangle.h"
#include "../scene/camera.h"

class Model : public VisibleObject
{
public:
	Model() {}
	Model(const Model &model);
	Model(Model &&model);
	~Model() = default;
	
	Model& operator=(const Model &model);
	Model& operator=(Model &&model);
	
	std::vector<Vertex>& get_vertices();
	std::vector<Triangle>& get_triangles();
	
	std::vector<Triangle> get_visible_sides(Camera &cm);
	
	void shift(double dx, double dy, double dz);
    void scale(double kx, double ky, double kz, Vertex pc=Vertex(0, 0, 0));
    void rotate(double ax, double ay, double az, Vertex pc=Vertex(0, 0, 0));
	
	void shift(std::vector<double> d);
	void scale(std::vector<double> k, Vertex pc = Vertex(0, 0, 0));
	void rotate(std::vector<double> a, Vertex pc = Vertex(0, 0, 0));
	
private:
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
};

typedef std::vector<std::shared_ptr<Model>>::iterator ModelIter;

#endif // MODEL_H
