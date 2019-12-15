#ifndef FLAG_H
#define FLAG_H

#include "../model/model.h"
#include "../model/mathvector.h"

class Node
{
public:
	Node(const Vertex& v, size_t index, double mass);
	~Node() = default;
	
	Vertex start_pos;
	double mass;
	double inv_mass;
	MathVector f;
	MathVector v;
	size_t vertex_index;
	std::shared_ptr<Vertex> vertex;
};

class Edge
{
public:
	Edge(const Node &node1, const Node &node2, double spring_rate,
		 double friction);
	~Edge() = default;
	
	size_t v1;
	size_t v2;
	double len_idle;
	double len_cur;
	double spring_rate;
	double friction;
};

class Flag
{
public:
	Flag(Vertex topleft, double w, double h, QColor colour);
	~Flag() = default;
	
	std::shared_ptr<Model> get_model();
	
private:
	Model model;
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	
	// std::vector<Vertex>& vertices;
};

#endif // FLAG_H
