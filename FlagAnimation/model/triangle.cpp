#include "triangle.h"

Triangle::Triangle(size_t i1, size_t i2, size_t i3, QColor c)
{
	vertex_indexes[0] = i1;
	vertex_indexes[1] = i2;
	vertex_indexes[2] = i3;
	colour = c;
}

Triangle::Triangle(const Triangle &tr)
{
	this->vertex_indexes[0] = tr.vertex_indexes[0];
	this->vertex_indexes[1] = tr.vertex_indexes[1];
	this->vertex_indexes[2] = tr.vertex_indexes[2];
	this->colour = tr.colour;
}

Triangle::Triangle(Triangle &&tr)
{
	this->vertex_indexes[0] = tr.vertex_indexes[0];
	this->vertex_indexes[1] = tr.vertex_indexes[1];
	this->vertex_indexes[2] = tr.vertex_indexes[2];
	this->colour = tr.colour;
	tr.~Triangle();
}

Triangle& Triangle::operator=(const Triangle &tr)
{
	this->vertex_indexes[0] = tr.vertex_indexes[0];
	this->vertex_indexes[1] = tr.vertex_indexes[1];
	this->vertex_indexes[2] = tr.vertex_indexes[2];
	this->colour = tr.colour;
	return *this;
}

Triangle& Triangle::operator=(Triangle &&tr)
{
	this->vertex_indexes[0] = tr.vertex_indexes[0];
	this->vertex_indexes[1] = tr.vertex_indexes[1];
	this->vertex_indexes[2] = tr.vertex_indexes[2];
	this->colour = tr.colour;
	tr.~Triangle();
	return *this;
}

size_t Triangle::get_vertex(size_t index)
{
	return vertex_indexes[index];
}

void Triangle::set_vertex(size_t index, size_t value)
{
	vertex_indexes[index] = value;
}

std::vector<Vertex> Triangle::get_vertices(std::vector<Vertex>& vertices)
{
	std::vector<Vertex> _vertices;
	for (size_t i = 0; i < 3; i++)
		_vertices.push_back(vertices[get_vertex(i)]);
	return _vertices;
}

QColor Triangle::get_color() const {return colour;}

void Triangle::set_color(QColor c) {colour = c;}
