#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include "../gui/drawer.h"


class DrawManager
{
public:
    DrawManager() = default;
    ~DrawManager() = default;
	
	void draw_model(BaseDrawer &drawer, ModelIter b, ModelIter e, Camera& cm);

private:
    static constexpr double coeff3D = 0.5;

    double get_x(double x, double z) const;
    double get_y(double y, double z) const;
};

#endif // DRAWMANAGER_H
