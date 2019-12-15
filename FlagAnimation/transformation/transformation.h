#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H


class BaseTransformation
{
public:
    BaseTransformation(double x, double y, double z) : _x(x), _y(y), _z(z) {}
    virtual ~BaseTransformation() = default;

    virtual bool is_shifting() = 0;
    virtual bool is_scaling() = 0;
    virtual bool is_rotation() = 0;

    double get_x() { return _x; }
    double get_y() { return _y; }
    double get_z() { return _z; }

protected:
    double _x, _y, _z;
};

namespace Transformations
{
class Shifting : public BaseTransformation
{
public:
	Shifting(double dx, double dy, double dz) :
		BaseTransformation(dx, dy, dz) {}
	~Shifting() = default;

	bool is_shifting() { return true; }
	bool is_scaling() { return false; }
	bool is_rotation() { return false; }
};

class Scaling : public BaseTransformation
{
public:
	Scaling(double kx, double ky, double kz) :
		BaseTransformation(kx, ky, kz) {}
	~Scaling() = default;

	bool is_shifting() { return false; }
	bool is_scaling() { return true; }
	bool is_rotation() { return false; }
};

class Rotation : public BaseTransformation
{
public:
	Rotation(double ax, double ay, double az) :
		BaseTransformation(ax, ay, az) {}
	~Rotation() = default;

	bool is_shifting() { return false; }
	bool is_scaling() { return false; }
	bool is_rotation() { return true; }
};
}

#endif // TRANSFORMATION_H
