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

std::vector<MathVector> Model::get_normals()
{
	Vertex v_zero(0, 0, 0);
	std::vector<MathVector> normals(vertices.size());
	std::vector<int> k(vertices.size());
	
	for (size_t i = 0; i < normals.size(); i++)
	{
		normals[i] = MathVector(0, 0, 0);
		k[i] = 0;
	}
	
	for (size_t i = 0; i < triangles.size(); i++)
	{
		std::vector<Vertex> v = triangles[i].get_vertices(vertices);
		
		MathVector vec[] = { MathVector(v_zero, v[0]),
							 MathVector(v_zero, v[1]),
							 MathVector(v_zero, v[2]) };
		
		MathVector n = (vec[2] - vec[0]) * (vec[1] - vec[0]);
		n.normalize();
		
		for (size_t j = 0; j < 3; j++)
		{
			normals[triangles[i].get_vertex(j)] += n;
			k[triangles[i].get_vertex(j)]++;
		}
	}
	
	for (size_t i = 0; i < normals.size(); i++)
		normals[i] /= double(k[i]);
	
	return normals;
}
