#include <cmath>
#include "vertex.h"

Vertex::Vertex(const Vertex &vertex)
{
	this->_x = vertex._x;
	this->_y = vertex._y;
	this->_z = vertex._z;
}

Vertex::Vertex(Vertex &&vertex)
{
	this->_x = vertex._x;
	this->_y = vertex._y;
	this->_z = vertex._z;
	vertex.~Vertex();
}

Vertex &Vertex::operator=(const Vertex &vertex)
{
	this->_x = vertex._x;
	this->_y = vertex._y;
	this->_z = vertex._z;
	return *this;
}

Vertex &Vertex::operator=(Vertex &&vertex)
{
	this->_x = vertex._x;
	this->_y = vertex._y;
	this->_z = vertex._z;
	vertex.~Vertex();
	return *this;
}

double Vertex::x()
{
	return _x;
}

double Vertex::y()
{
	return _y;
}

double Vertex::z()
{
	return _z;
}

void Vertex::set_x(double x)
{
	_x = x;
}

void Vertex::set_y(double y)
{
	_y = y;
}

void Vertex::set_z(double z)
{
	_z = z;
}

void Vertex::set(double x, double y, double z)
{
	set_x(x);
	set_y(y);
	set_z(z);
}

void Vertex::shift(double dx, double dy, double dz)
{
	_x += dx;
	_y += dy;
	_z += dz;
}

void Vertex::scale(double kx, double ky, double kz, Vertex pc)
{
	double px = pc.x(), py = pc.y(), pz = pc.y();
	_x = px + (_x - px) * kx;
	_y = py + (_y - py) * ky;
	_z = pz + (_z - pz) * kz;
}

void Vertex::rotate_x(double angle, Vertex pc)
{
	double py = pc.y(), pz = pc.z();
	double dy = _y - py, dz = _z - pz;
	_y = py + dy * cos(angle) + dz * sin(angle);
	_z = pz - dy * sin(angle) + dz * cos(angle);
}

void Vertex::rotate_y(double angle, Vertex pc)
{
	double pz = pc.z(), px = pc.x();
	double dz = _z - pz, dx = _x - px;
	_z = pz + dz * cos(angle) + dx * sin(angle);
	_x = px - dz * sin(angle) + dx * cos(angle);
}

void Vertex::rotate_z(double angle, Vertex pc)
{
	double px = pc.x(), py = pc.y();
	double dx = _x - px, dy = _y - py;
	_x = px + dx * cos(angle) + dy * sin(angle);
	_y = py - dx * sin(angle) + dy * cos(angle);
}

void Vertex::shift(std::vector<double> d)
{
	_x += d[0];
	_y += d[1];
	_z += d[2];
}

void Vertex::scale(std::vector<double> k, Vertex pc)
{
	double px = pc.x(), py = pc.y(), pz = pc.y();
	_x = px + (_x - px) * k[0];
	_y = py + (_y - py) * k[1];
	_z = pz + (_z - pz) * k[2];
}

void Vertex::rotate(std::vector<double> a, Vertex pc)
{
	double px = pc.x(), py = pc.y(), pz = pc.z();
	double dx, dy, dz;
	
	dy = _y - py;
	dz = _z - pz;
	_y = py + dy * cos(a[0]) + dz * sin(a[0]);
	_z = pz - dy * sin(a[0]) + dz * cos(a[0]);
	
	dz = _z - pz;
	dx = _x - px;
	_z = pz + dz * cos(a[1]) + dx * sin(a[1]);
	_x = px - dz * sin(a[1]) + dx * cos(a[1]);
	
	dx = _x - px;
	dy = _y - py;
	_x = px + dx * cos(a[2]) + dy * sin(a[2]);
	_y = py - dx * sin(a[2]) + dy * cos(a[2]);
}

double distance(Vertex p1, Vertex p2)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();
	double dz = p2.z() - p2.z();
	return sqrt(dx * dx + dy * dy + dz * dz);
}
