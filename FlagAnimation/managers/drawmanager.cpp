#include "drawmanager.h"
#include "../exceptions/drawexception.h"

void DrawManager::draw_model(BaseDrawer &drawer, ModelIter b, ModelIter e,
							 Camera& cm)
{
	std::vector<Model> figures;
    for (ModelIter iter = b; iter != e; ++iter)
    {
		if (!(*iter))
            throw NoObjectToDrawException();
		
		Model figure = *(*iter);
		
		std::vector<Vertex> &vertices = figure.get_vertices();
		if (vertices.empty())
			throw NoVertexToDrawException();
		
		std::vector<Triangle> &triangles = figure.get_triangles();
		if (triangles.empty())
			throw NoTriangleToDrawException();
		
		figure.shift(cm.get_shift_params());
		figure.scale(cm.get_scale_params(), cm.get_center());
		figure.rotate(cm.get_rotate_params(), cm.get_center());
		
		figures.push_back(figure);
	}
	drawer.draw_scene(figures, cm);
}

double DrawManager::get_x(double x, double z) const
{
    return x + z * coeff3D;
}

double DrawManager::get_y(double y, double z) const
{
    return -y - z * coeff3D;
}
