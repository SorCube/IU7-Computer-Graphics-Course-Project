#include "model.h"
#include "mathvector.h"

Model::Model(const Model &model)
{
	this->triangles = model.triangles;
	this->vertices = model.vertices;
}

Model::Model(Model &&model)
{
	this->triangles = model.triangles;
	this->vertices = model.vertices;
	model.~Model();
}

Model& Model::operator=(const Model &model)
{
	this->triangles = model.triangles;
	this->vertices = model.vertices;
	return *this;
}

Model& Model::operator=(Model &&model)
{
	this->triangles = model.triangles;
	this->vertices = model.vertices;
	model.~Model();
	return *this;
}

std::vector<Vertex>& Model::get_vertices()
{
	return vertices;
}

std::vector<Triangle>& Model::get_triangles()
{
	return triangles;
}

std::vector<Triangle> Model::get_visible_sides(Camera &cm)
{
	std::vector<Triangle> sides;
	for (auto tr : triangles)
    {
        std::vector<Vertex> verts = tr.get_vertices(vertices);
        MathVector v1 = MathVector(verts[1], verts[2]);
        MathVector v2 = MathVector(verts[1], verts[0]);
        MathVector n = v1 * v2;
        MathVector v = MathVector(cm.get_pos(), verts[1]);

        v.normalize();
        n.normalize();

        double comp = v & n;
        /*if (inverted)
            comp *= -1;*/
        if (comp >= 0)
            sides.push_back(tr);
    }
	return sides;
}

void Model::shift(double dx, double dy, double dz)
{
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].shift(dx, dy, dz);
}

void Model::scale(double kx, double ky, double kz, Vertex pc)
{
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].scale(kx, ky, kz, pc);
}

void Model::rotate(double ax, double ay, double az, Vertex pc)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].rotate_x(ax, pc);
		vertices[i].rotate_y(ay, pc);
		vertices[i].rotate_z(az, pc);
	}
}

void Model::shift(std::vector<double> d)
{
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].shift(d);
}

void Model::scale(std::vector<double> k, Vertex pc)
{
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].scale(k, pc);
}

void Model::rotate(std::vector<double> a, Vertex pc)
{
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].rotate(a, pc);
}
