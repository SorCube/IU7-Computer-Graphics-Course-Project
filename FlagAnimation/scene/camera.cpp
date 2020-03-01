#include <cmath>
#include "camera.h"

Camera::Camera(Vertex c) : pos(c),
	shift_params(3, 0), scale_params(3, 1), rotate_params(3, 0)
{
	// pos = Vertex(c.x(), c.y(), -10000);
	center = Vertex(0, 0, 0);
}

Vertex& Camera::get_pos()
{
	return pos;
}

void Camera::set_pos(const Vertex& v)
{
	pos = v;
}

Vertex& Camera::get_center()
{
	return center;
}

void Camera::set_center(const Vertex& v)
{
	center = v;
}

double Camera::get_shift_x() const {return shift_params[0];}
double Camera::get_shift_y() const {return shift_params[1];}
double Camera::get_shift_z() const {return shift_params[2];}

double Camera::get_scale_x() const {return scale_params[0];}
double Camera::get_scale_y() const {return scale_params[1];}
double Camera::get_scale_z() const {return scale_params[2];}

double Camera::get_rotate_x() const {return rotate_params[0];}
double Camera::get_rotate_y() const {return rotate_params[1];}
double Camera::get_rotate_z() const {return rotate_params[2];}

std::vector<double>& Camera::get_shift_params() {return shift_params;}
std::vector<double>& Camera::get_scale_params() {return scale_params;}
std::vector<double>& Camera::get_rotate_params() {return rotate_params;}

std::vector<double> Camera::get_inv_shift_params()
{
	std::vector<double> params = shift_params;
	for (auto p : params)
		p = -p;
	return params;
}

std::vector<double> Camera::get_inv_scale_params()
{
	std::vector<double> params = scale_params;
	for (auto p : params)
		p = 1 / p;
	return params;
}

std::vector<double> Camera::get_inv_rotate_params()
{
	std::vector<double> params = rotate_params;
	for (auto p : params)
		p = -p;
	return params;
}

void Camera::shift(double x, double y, double z)
{
    shift_params[0] += x;
    shift_params[1] += y;
    shift_params[2] += z;
}

void Camera::scale(double x, double y, double z)
{
    scale_params[0] *= x;
    scale_params[1] *= y;
    scale_params[2] *= z;
}

void Camera::rotate(double x, double y, double z)
{
    rotate_params[0] += x;
    rotate_params[1] += y;
    rotate_params[2] += z;
}

double Camera::distance(Vertex &v)
{
	double dx = shift_params[0] - v.x();
	double dy = shift_params[1] - v.y();
	double dz = shift_params[2] - v.z();
	return sqrt(dx * dx + dy * dy + dz * dz);
}
