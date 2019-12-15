#include "flag.h"

Node::Node(const Vertex &v, size_t index, double mass) :
	start_pos(v), mass(mass), inv_mass((mass == 0) ? 0 : 1 / mass),
	f(0, 0, 0), v(0, 0, 0),
	vertex_index(index), vertex(std::make_shared<Vertex>(v)) {}

Edge::Edge(const Node &node1, const Node &node2, double spring_rate,
		   double friction) :
	v1(node1.vertex_index), v2(node2.vertex_index),
	spring_rate(spring_rate), friction(friction)
{
	len_idle = distance(*(node1.vertex), *(node2.vertex));
	len_cur = len_idle;
}

Flag::Flag(Vertex topleft, double w, double h, QColor colour) :
	model()
{
	const double grad_w = 50;
	const double grad_h = 20;
	
	std::vector<Vertex>& vertices = model.get_vertices();
	std::vector<Triangle>& triangles = model.get_triangles();
	
	double dx = w / grad_w;
	double dz = -(h / grad_h);
	double y = topleft.y();
	
	size_t n = grad_h + 1, m = grad_w + 1;
	
	double z = topleft.z();
	size_t ind = 0;
	for (size_t i = 0; i < n; i++)
	{
		double x = topleft.x();
		for (size_t j = 0; j < m; j++)
		{
			vertices.push_back(Vertex(x, y, z));
			nodes.push_back(Node(vertices[ind], ind, j ? 1 : 0));
			ind++;
			x += dx;
		}
		z += dz;
	}
	
	for (size_t j = 0; j < m - 1; j++)
	{
		triangles.push_back(Triangle(j, j + 1, j + m, colour));
		edges.push_back(Edge(nodes[j], nodes[j + 1], 5, 1));
		edges.push_back(Edge(nodes[j + 1], nodes[j + m], 5, 1));
		edges.push_back(Edge(nodes[j + m], nodes[j], 5, 1));
	}
	
	ind = m;
	for (size_t i = 1; i < n - 1; i++, ind += m)
		for (size_t j = ind; j < ind + m - 1; j++)
		{
			triangles.push_back(Triangle(j, j + 1, j + m, colour));
			edges.push_back(Edge(nodes[j], nodes[j + 1], 5, 1));
			edges.push_back(Edge(nodes[j + 1], nodes[j + m], 5, 1));
			edges.push_back(Edge(nodes[j + m], nodes[j], 5, 1));
			
			triangles.push_back(Triangle(j - m + 1, j, j + 1, colour));
			edges.push_back(Edge(nodes[j - m + 1], nodes[j], 5, 1));
			edges.push_back(Edge(nodes[j], nodes[j + 1], 5, 1));
			edges.push_back(Edge(nodes[j + 1], nodes[j - m + 1], 5, 1));
		}
	
	for (size_t j = ind; j < ind + m - 1; j++)
	{
		triangles.push_back(Triangle(j - m + 1, j, j + 1, colour));
		edges.push_back(Edge(nodes[j - m + 1], nodes[j], 5, 1));
		edges.push_back(Edge(nodes[j], nodes[j + 1], 5, 1));
		edges.push_back(Edge(nodes[j + 1], nodes[j - m + 1], 5, 1));
	}
}

std::shared_ptr<Model> Flag::get_model()
{
	return std::make_shared<Model>(model);
}
