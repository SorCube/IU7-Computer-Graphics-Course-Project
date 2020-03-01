#ifndef FLAG_H
#define FLAG_H

#include "../model/model.h"
#include "../model/mathvector.h"

class Node
{
public:
	Node(const Vertex& v, size_t index, double mass, double friction);
	~Node() = default;
	
	Vertex start_pos;
	double mass;
	double inv_mass;
	double friction;
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
	double len_rest;
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
	
	void set_mass(double mass);
	void set_friction(double friction);
	void set_spring(double spring_rate);
	
	void reset();
	void update(MathVector wind_vector, int msec);
	void update_thread(MathVector wind_vector, int msec);
	
private:
	Model model;
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	
	Model start_model;
	std::vector<Node> start_nodes;
	std::vector<Edge> start_edges;
	
	void update_nodes_init(size_t start, size_t end);
	void update_wind_tr(MathVector& wv, size_t start, size_t end,
						std::vector<Vertex>& v, std::vector<Triangle>& tr);
	void update_edges(size_t start, size_t end, std::vector<Vertex>& v);
	void update_nodes(int msec, size_t start, size_t end,
					  std::vector<Vertex>& v);
};

#endif // FLAG_H
