#ifndef MATHVECTOR_H
#define MATHVECTOR_H

#include "vertex.h"


class MathVector
{
public:
	MathVector() : _x(0), _y(0), _z(0) {}
	MathVector(double x, double y, double z) : _x(x), _y(y), _z(z) {}
	MathVector(Vertex v1, Vertex v2);
	MathVector(const MathVector &v);
	MathVector(MathVector &&v);
	
	MathVector& operator=(const MathVector &v);
	MathVector& operator=(MathVector &&v);
	
	double x();
	double y();
	double z();
	
	void set_x(double x);
	void set_y(double y);
	void set_z(double z);
	void set(double x, double y, double z);
	
	double length();
    void normalize();
	
	MathVector operator*(const MathVector& v) const;
	MathVector& operator*=(const MathVector& v);
	
	MathVector operator*(double k) const;
	MathVector& operator*=(double k);
	
	MathVector operator+(const MathVector& v) const;
	MathVector& operator+=(const MathVector& v);
	
	MathVector operator-(const MathVector& v) const;
	MathVector& operator-=(const MathVector& v);

    double operator&(const MathVector& v) const;
    double operator^(MathVector& v);
	
private:
	double _x, _y, _z;
};

#endif // MATHVECTOR_H
