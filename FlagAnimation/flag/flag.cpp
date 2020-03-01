#include <thread>
#include "flag.h"

Node::Node(const Vertex &v, size_t index, double mass, double friction) :
	start_pos(v), mass(mass), inv_mass((mass == 0) ? 0 : 1 / mass),
	friction(friction),
	f(0, 0, 0), v(0, 0, 0),
	vertex_index(index), vertex(std::make_shared<Vertex>(v)) {}

Edge::Edge(const Node &node1, const Node &node2, double spring_rate,
		   double friction) :
	v1(node1.vertex_index), v2(node2.vertex_index),
	spring_rate(spring_rate), friction(friction)
{
	len_rest = distance(*(node1.vertex), *(node2.vertex));
	len_cur = len_rest;
}

Flag::Flag(Vertex topleft, double w, double h, QColor colour) :
	model()
{
	const double grad_w = 50;
	const double grad_h = 25;
	
	const double fric = 0.5;
	const double spring = 10;
	
	const double mass = 0.5;
	
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
			nodes.push_back(Node(vertices[ind], ind, j ? mass : 0, fric));
			ind++;
			x += dx;
		}
		z += dz;
	}
	
	ind = 0;
	for (size_t i = 0; i < n - 1; i++, ind += m)
		for (size_t j = ind; j < ind + m - 1; j++)
		{
			triangles.push_back(Triangle(j, j + m, j + 1, colour));
			triangles.push_back(Triangle(j + 1, j + m, j + m + 1, colour));
			
			edges.push_back(Edge(nodes[j], nodes[j + 1], spring, fric));
			edges.push_back(Edge(nodes[j], nodes[j + m], spring, fric));
			edges.push_back(Edge(nodes[j + m + 1], nodes[j + 1], spring, fric));
			edges.push_back(Edge(nodes[j + m], nodes[j + m + 1], spring, fric));
			
			edges.push_back(Edge(nodes[j], nodes[j + m + 1], spring, fric));
			edges.push_back(Edge(nodes[j + 1], nodes[j + m], spring, fric));
		}
	
	for (size_t j = ind; j < ind + m - 1; j++)
		edges.push_back(Edge(nodes[j], nodes[j + 1], spring, fric));
	
	start_model = model;
	start_nodes = nodes;
	start_edges = edges;
}

std::shared_ptr<Model> Flag::get_model()
{
	return std::make_shared<Model>(model);
}

void Flag::set_mass(double mass)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].mass != 0)
		{
			nodes[i].mass = mass;
			nodes[i].inv_mass = 1 / mass;
		}
	}
}

void Flag::set_friction(double friction)
{
	for (size_t i = 0; i < nodes.size(); i++)
		nodes[i].friction = friction;
	for (size_t i = 0; i < edges.size(); i++)
		edges[i].friction = friction;
}

void Flag::set_spring(double spring_rate)
{
	for (size_t i = 0; i < edges.size(); i++)
		edges[i].spring_rate = spring_rate;
}

void Flag::reset()
{
	model = start_model;
	edges = start_edges;
	nodes = start_nodes;
}

void Flag::update(MathVector wv, int msec)
{
	update_thread(wv, msec);
	return;
	
	for (size_t i = 0; i < nodes.size(); i++)
	{
		nodes[i].f = MathVector(0, 0, -nodes[i].mass * 9.8);
		nodes[i].f += MathVector(-nodes[i].friction * nodes[i].v);
	}
	
	std::vector<Vertex>& vertices = model.get_vertices();
	std::vector<Triangle>& triangles = model.get_triangles();
	
	for (auto tr : triangles)
	{
		std::vector<Vertex> tr_v = tr.get_vertices(vertices);
		
		Vertex v_zero(0, 0, 0);
		MathVector vec[] = { MathVector(v_zero, tr_v[0]),
							 MathVector(v_zero, tr_v[1]),
							 MathVector(v_zero, tr_v[2]) };
		
		MathVector n = (vec[2] - vec[0]) * (vec[1] - vec[0]);
		n.normalize();
		n *= n & wv;		// value of scalar production - wind strength;
		
		for (size_t i = 0; i < 3; i++)
			nodes[tr.get_vertex(i)].f += n;
	}
	
	for (size_t i = 0; i < edges.size(); i++)
	{
		Edge &e = edges[i];
		Vertex& v1 = vertices[e.v1];
		Vertex& v2 = vertices[e.v2];
		e.len_cur = distance(v1, v2);
		
		MathVector spring_force(v1, v2);
		spring_force.normalize();
		
		double spring_k = e.spring_rate * (e.len_cur - e.len_rest);
		
		MathVector rel_velocity = nodes[e.v2].v - nodes[e.v1].v;
		double velocity = (rel_velocity & spring_force);
		if (e.len_cur != 0)
			velocity /= e.len_cur;
		else
			velocity = 0;
		
		double damping_k = e.friction * velocity;
		
		spring_force *= spring_k + damping_k;
		
		nodes[e.v1].f += spring_force;
		nodes[e.v2].f -= spring_force;
	}
	
	for (size_t i = 0; i < nodes.size(); i++)
	{
		double t = double(msec) / 1000;
		MathVector accel = t * nodes[i].f * nodes[i].inv_mass;
		nodes[i].v += accel;
		MathVector d = t * nodes[i].v;
		vertices[nodes[i].vertex_index].shift(d.x(), d.y(), d.z());
	}
}


void Flag::update_thread(MathVector wv, int msec)
{
	std::vector<Vertex>& v = model.get_vertices();
	std::vector<Triangle>& tr = model.get_triangles();
	
	size_t dn = nodes.size() / 4;
	std::vector<std::thread> threads_init;
	for (size_t k = 0, i = 0; k < 4; k++, i += dn)
		threads_init.push_back(std::thread(Flag::update_nodes_init,
										   this, i,
										   (k == 3 ? nodes.size() : i + dn)));
	for (size_t k = 0; k < 4; k++)
		threads_init[k].join();
	
	size_t dt = tr.size() / 4;
	std::vector<std::thread> threads_tr;
	for (size_t k = 0, i = 0; k < 4; k++, i += dt)
		threads_tr.push_back(std::thread(Flag::update_wind_tr,
										 this, std::ref(wv), i,
										 (k == 3 ? tr.size() : i + dt),
										 std::ref(v),
										 std::ref(tr)));
	for (size_t k = 0; k < 4; k++)
		threads_tr[k].join();
	
	size_t de = edges.size() / 4;
	std::vector<std::thread> threads_edges;
	for (size_t k = 0, i = 0; k < 4; k++, i += de)
		threads_edges.push_back(std::thread(Flag::update_edges,
											this, i,
											(k == 3 ? edges.size() : i + de),
											std::ref(v)));
	for (size_t k = 0; k < 4; k++)
		threads_edges[k].join();
	
	std::vector<std::thread> threads_nodes;
	for (size_t k = 0, i = 0; k < 4; k++, i += dn)
		threads_nodes.push_back(std::thread(Flag::update_nodes,
											this, msec, i,
											(k == 3 ? nodes.size() : i + dn),
											std::ref(v)));
	for (size_t k = 0; k < 4; k++)
		threads_nodes[k].join();
}

void Flag::update_nodes_init(size_t start, size_t end)
{
	for (size_t i = start; i < end; i++)
		nodes[i].f = MathVector(0, 0, 0);
}

void Flag::update_wind_tr(MathVector& wv, size_t start, size_t end,
						  std::vector<Vertex>& v, std::vector<Triangle>& tr)
{
	for (size_t i = start; i < end; i++)
	{
		std::vector<Vertex> tr_v = tr[i].get_vertices(v);
		
		Vertex v_zero(0, 0, 0);
		MathVector vec[] = { MathVector(v_zero, tr_v[0]),
							 MathVector(v_zero, tr_v[1]),
							 MathVector(v_zero, tr_v[2]) };
		
		MathVector n = (vec[2] - vec[0]) * (vec[1] - vec[0]);
		n.normalize();
		n *= n & wv;		// value of scalar production - wind strength
		
		for (size_t j = 0; j < 3; j++)
			nodes[tr[i].get_vertex(j)].f += n;
	}
}

void Flag::update_edges(size_t start, size_t end, std::vector<Vertex>& v)
{
	for (size_t i = start; i < end; i++)
	{
		Edge &e = edges[i];
		Vertex& v1 = v[e.v1];
		Vertex& v2 = v[e.v2];
		e.len_cur = distance(v1, v2);
		
		MathVector spring_force(v1, v2);
		spring_force.normalize();
		
		double spring_k = e.spring_rate * (e.len_cur - e.len_rest);
		
		MathVector rel_velocity = nodes[e.v2].v - nodes[e.v1].v;
		double velocity = (rel_velocity & spring_force);
		if (e.len_cur != 0)
			velocity /= e.len_cur;
		else
			velocity = 0;
		
		double damping_k = e.friction * velocity;
		
		spring_force *= spring_k + damping_k;
		
		nodes[e.v1].f += spring_force;
		nodes[e.v2].f -= spring_force;
	}
}

void Flag::update_nodes(int msec, size_t start, size_t end,
						std::vector<Vertex>& v)
{
	for (size_t i = start; i < end; i++)
	{
		nodes[i].f += MathVector(0, 0, -nodes[i].mass * 9.8);
		nodes[i].f += MathVector(-nodes[i].friction * nodes[i].v);
		
		double t = double(msec) / 1000;
		MathVector accel = t * nodes[i].f * nodes[i].inv_mass;
		nodes[i].v += accel;
		MathVector d = t * nodes[i].v;
		v[nodes[i].vertex_index].shift(d.x(), d.y(), d.z());
	}
}
