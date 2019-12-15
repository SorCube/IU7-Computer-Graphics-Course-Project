#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "../model/vertex.h"
#include "../model/object.h"

class Camera : public InvisibleObject
{
public:
	Camera(Vertex c);
    ~Camera() = default;
	
	Vertex& get_pos();
	void set_pos(const Vertex& v);
	
	Vertex& get_center();
	void set_center(const Vertex& v);

    double get_shift_x() const;
    double get_shift_y() const;
    double get_shift_z() const;
	
    double get_scale_x() const;
    double get_scale_y() const;
    double get_scale_z() const;

    double get_rotate_x() const;
    double get_rotate_y() const;
    double get_rotate_z() const;
	
	std::vector<double>& get_shift_params();
	std::vector<double>& get_scale_params();
	std::vector<double>& get_rotate_params();
	
	std::vector<double> get_inv_shift_params();
	std::vector<double> get_inv_scale_params();
	std::vector<double> get_inv_rotate_params();

    void shift(double x, double y, double z);
    void scale(double x, double y, double z);
    void rotate(double x, double y, double z);
	
	double distance(Vertex &v);

private:
	Vertex pos, center;
    std::vector<double> shift_params, scale_params, rotate_params;
};

typedef std::vector<std::shared_ptr<Camera>>::iterator CameraIter;

#endif // CAMERA_H
