#ifndef POINT_H
#define POINT_H

#include <vector>

class Vertex
{
public:
	Vertex() : _x(0), _y(0), _z(0) {}
	Vertex(double x, double y, double z) : _x(x), _y(y), _z(z) {}
	Vertex(const Vertex &vertex);
	Vertex(Vertex &&vertex);
	
	Vertex& operator=(const Vertex &vertex);
	Vertex& operator=(Vertex &&vertex);
	
	double x();
	double y();
	double z();
	
	void set_x(double x);
	void set_y(double y);
	void set_z(double z);
	void set(double x, double y, double z);
	
	void shift(double dx, double dy, double dz);
	void scale(double kx, double ky, double kz, Vertex pc = Vertex(0, 0, 0));
	void rotate_x(double angle, Vertex pc = Vertex(0, 0, 0));
	void rotate_y(double angle, Vertex pc = Vertex(0, 0, 0));
	void rotate_z(double angle, Vertex pc = Vertex(0, 0, 0));
	
	void shift(std::vector<double> d);
	void scale(std::vector<double> k, Vertex pc = Vertex(0, 0, 0));
	void rotate(std::vector<double> a, Vertex pc = Vertex(0, 0, 0));
	
private:
	double _x, _y, _z;
};

double distance(Vertex p1, Vertex p2);

#endif // POINT_H
