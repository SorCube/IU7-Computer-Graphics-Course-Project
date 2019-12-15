#include <cmath>
#include "mathvector.h"

MathVector::MathVector(Vertex v1, Vertex v2)
{
	_x = v2.x() - v1.x();
    _y = v2.y() - v1.y();
    _z = v2.z() - v1.z();
}

MathVector::MathVector(const MathVector &v)
{
	this->_x = v._x;
	this->_y = v._y;
	this->_z = v._z;
}

MathVector::MathVector(MathVector &&v)
{
	this->_x = v._x;
	this->_y = v._y;
	this->_z = v._z;
	v.~MathVector();
}

MathVector& MathVector::operator=(const MathVector &v)
{
	this->_x = v._x;
	this->_y = v._y;
	this->_z = v._z;
	return *this;
}

MathVector& MathVector::operator=(MathVector &&v)
{
	this->_x = v._x;
	this->_y = v._y;
	this->_z = v._z;
	v.~MathVector();
	return *this;
}

double MathVector::x()
{
	return _x;
}

double MathVector::y()
{
	return _y;
}

double MathVector::z()
{
	return _z;
}

void MathVector::set_x(double x)
{
	_x = x;
}

void MathVector::set_y(double y)
{
	_y = y;
}

void MathVector::set_z(double z)
{
	_z = z;
}

void MathVector::set(double x, double y, double z)
{
	set_x(x);
	set_y(y);
	set_z(z);
}

double MathVector::length()
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}

void MathVector::normalize()
{
    double len = length();
    _x /= len;
    _y /= len;
    _z /= len;
}

MathVector MathVector::operator*(const MathVector& v) const
{
	double x = _y * v._z - _z * v._y;
	double y = _z * v._x - _x * v._z;
	double z = _x * v._y - _y * v._x;
	return MathVector(x, y, z);
}

MathVector& MathVector::operator*=(const MathVector& v)
{
	_x = _y * v._z - _z * v._y;
	_y = _z * v._x - _x * v._z;
	_z = _x * v._y - _y * v._x;
	return *this;
}

MathVector MathVector::operator*(double k) const
{
	return MathVector(_x * k, _y * k, _z * k);
}

MathVector &MathVector::operator*=(double k)
{
	_x *= k;
	_y *= k;
	_z *= k;
	return *this;
}

MathVector MathVector::operator+(const MathVector& v) const
{
	return MathVector(_x + v._x, _y + v._y, _z + v._z);
}

MathVector& MathVector::operator+=(const MathVector& v)
{
	_x += v._x;
	_y += v._y;
	_z += v._z;
	return *this;
}

MathVector MathVector::operator-(const MathVector& v) const
{
	return MathVector(_x - v._x, _y - v._y, _z - v._z);
}

MathVector& MathVector::operator-=(const MathVector& v)
{
	_x -= v._x;
	_y -= v._y;
	_z -= v._z;
	return *this;
}

double MathVector::operator&(const MathVector& v) const
{
   return _x * v._x + _y * v._y + _z * v._z;
}

double MathVector::operator^(MathVector& v)
{
	return acos((*this & v) / (length() * v.length()));
}
