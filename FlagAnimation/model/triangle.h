#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cstdio>
#include <vector>
#include <QColor>
#include "vertex.h"

class Triangle
{
public:
	Triangle(size_t i1, size_t i2, size_t i3, QColor c=QColor(255, 0, 0));
	Triangle(const Triangle &tr);
	Triangle(Triangle &&tr);
	
	Triangle& operator=(const Triangle &tr);
	Triangle& operator=(Triangle &&tr);
	
	size_t get_vertex(size_t index);
	void set_vertex(size_t index, size_t value);
	
	std::vector<Vertex> get_vertices(std::vector<Vertex>& vertices);
	
	QColor get_color() const;
	void set_color(QColor c);

private:
	size_t vertex_indexes[3];
	QColor colour;
};

#endif // TRIANGLE_H
