#define _USE_MATH_DEFINES
#include <cmath>
#include "modelcreator.h"

Model PlateCreator::create(Vertex c, double w, double h, QColor colour)
{
	Model plate;
	std::vector<Vertex>& vertices = plate.get_vertices();
	std::vector<Triangle>& triangles = plate.get_triangles();
	
	w /= 2;
	h /= 2;
	
	vertices.push_back(Vertex(c.x() - w, c.y() - h, c.z()));
	vertices.push_back(Vertex(c.x() - w, c.y() + h, c.z()));
	vertices.push_back(Vertex(c.x() + w, c.y() + h, c.z()));
	vertices.push_back(Vertex(c.x() + w, c.y() - h, c.z()));
	
	triangles.push_back(Triangle(0, 1, 3, colour));
	triangles.push_back(Triangle(2, 3, 1, colour));
	
	return plate;
}

Model FlexRectCreator::create(Vertex c, double w, double h,
							  size_t grad_w, size_t grad_h, QColor colour)
{
	Model rect;
	std::vector<Vertex>& vertices = rect.get_vertices();
	std::vector<Triangle>& triangles = rect.get_triangles();
	
	double dx = w / grad_w;
	double dy = h / grad_h;
	double z = c.z();
	
	size_t n = grad_h + 1, m = grad_w + 1;
	
	double y = c.y() - h / 2;
	for (size_t i = 0; i < n; i++)
	{
		double x = c.x() - w / 2;
		for (size_t j = 0; j < m; j++)
		{
			vertices.push_back(Vertex(x, y, z));
			x += dx;
		}
		y += dy;
	}
	
	for (size_t j = 0; j < m - 1; j++)
		triangles.push_back(Triangle(j, j + 1, j + m, colour));
	
	size_t ind = m;
	for (size_t i = 1; i < n - 1; i++, ind += m)
		for (size_t j = ind; j < ind + m - 1; j++)
		{
			triangles.push_back(Triangle(j, j + 1, j + m, colour));
			triangles.push_back(Triangle(j + 1, j - m + 1, j, colour));
		}
	
	for (size_t j = ind; j < ind + m - 1; j++)
		triangles.push_back(Triangle(j + 1, j - m + 1, j, colour));
	
	return rect;
}

Model ParallelepipedCreator::create(Vertex pc, double a, double b,
									double c, QColor colour)
{
	Model par;
	std::vector<Vertex>& vertices = par.get_vertices();
	std::vector<Triangle>& triangles = par.get_triangles();
	
	a /= 2;
	b /= 2;
	c /= 2;
	
	vertices.push_back(Vertex(pc.x() - a, pc.y() - b, pc.z() - c));
	vertices.push_back(Vertex(pc.x() - a, pc.y() - b, pc.z() + c));
	vertices.push_back(Vertex(pc.x() - a, pc.y() + b, pc.z() - c));
	vertices.push_back(Vertex(pc.x() - a, pc.y() + b, pc.z() + c));
	
	vertices.push_back(Vertex(pc.x() + a, pc.y() + b, pc.z() - c));
	vertices.push_back(Vertex(pc.x() + a, pc.y() + b, pc.z() + c));
	vertices.push_back(Vertex(pc.x() + a, pc.y() - b, pc.z() - c));
	vertices.push_back(Vertex(pc.x() + a, pc.y() - b, pc.z() + c));
	
	triangles.push_back(Triangle(1, 3, 0, colour));
	triangles.push_back(Triangle(2, 0, 3, colour));
	triangles.push_back(Triangle(3, 5, 2, colour));
	triangles.push_back(Triangle(4, 2, 5, colour));
	triangles.push_back(Triangle(5, 7, 4, colour));
	triangles.push_back(Triangle(6, 4, 7, colour));
	triangles.push_back(Triangle(7, 1, 6, colour));
	triangles.push_back(Triangle(0, 6, 1, colour));
	
	triangles.push_back(Triangle(1, 7, 3, colour));
	triangles.push_back(Triangle(5, 3, 7, colour));
	triangles.push_back(Triangle(2, 4, 0, colour));
	triangles.push_back(Triangle(6, 0, 4, colour));
	
	return par;
}

Model CylinderCreator::create(Vertex center, double rad, double height,
							  size_t grad, QColor colour)
{
	Model cylinder;
    std::vector<Vertex>& vertices = cylinder.get_vertices();
	std::vector<Triangle>& triangles = cylinder.get_triangles();
	
	double ang = 0, d_ang = 2 * M_PI / double(grad);
	
	// bottom circle
	vertices.push_back(center);
	double z = center.z();
	
	ang = 0;
	for (size_t i = 0; i < grad; i++, ang += d_ang)
	{
		double x = center.x() + rad * cos(ang);
		double y = center.y() + rad * sin(ang);
		vertices.push_back(Vertex(x, y, z));
	}
	
	for (size_t i = 1; i < grad; i++)
        triangles.push_back(Triangle(0, i, i + 1, colour));
    triangles.push_back(Triangle(0, grad, 1, colour));
	
	// top circle
	Vertex top_center = center;
	top_center.shift(0, 0, height);
	vertices.push_back(top_center);
	
	size_t ic = vertices.size() - 1;
	z = top_center.z();
	
	ang = 0;
	for (size_t i = 0; i < grad; i++, ang += d_ang)
	{
		double x = center.x() + rad * cos(ang);
		double y = center.y() + rad * sin(ang);
		vertices.push_back(Vertex(x, y, z));
	}
	
    for (size_t i = ic + 1; i < ic + grad; i++)
        triangles.push_back(Triangle(ic, i, i + 1, colour));
    triangles.push_back(Triangle(ic, ic + grad, ic + 1, colour));
	
    // side parts
    for (size_t i = 1; i < grad; i++)
	{
        triangles.push_back(Triangle(i, i + 1, i + grad + 1, colour));
        triangles.push_back(Triangle(i + grad + 1, i + grad + 2, i + 1,
									 colour));
    }
    triangles.push_back(Triangle(grad, 1, 2 * grad + 1, colour));
    triangles.push_back(Triangle(2*grad + 1, grad + 2, 1, colour));

    return cylinder;
}
