#include <vector>
#include <cmath>
#include "drawer.h"

typedef struct
{
	double x;
	double y;
} Point;

ModelDrawer::ModelDrawer(Canvas* canv) :
	BaseDrawer(),
	canvas(canv)
{
	LC = QColor("black");

    light = Vertex(-500, -500, 1000);

    z_buf = new int*[IMG_SIZE];
    c_buf = new QColor*[IMG_SIZE];

    for (int i = 0; i < IMG_SIZE; ++i)
    {
        z_buf[i] = new int[IMG_SIZE];
        c_buf[i] = new QColor[IMG_SIZE];
    }
}

void ModelDrawer::draw_edge(Vertex v1, Vertex v2, QColor colour)
{
	if (v1.x() == v2.x() && v1.y() == v2.y())
		return;
	
	double xlen = v2.x() - v1.x();
	double ylen = v2.y() - v1.y();
	double zlen = v2.z() - v1.z();
	double len = 1;
	if (fabs(xlen) > fabs(ylen))
		len =fabs(xlen);
	else
		len = fabs(ylen);
	
	double dx = xlen / len, dy = ylen / len, dz = zlen / len;
	double x = v1.x(), y = v1.y(), z = v1.z();
	
	for (int i = 1; i <= dx + len; i++)
	{
		int idx = int(round(x)), idy = int(round(y));
		
		if (idx >= 0 && idx < IMG_SIZE && idy > 0 && idy < IMG_SIZE &&
				z < z_buf[int(x)][int(y)])
		{
			z_buf[idx][idy] = z;
			c_buf[idx][idy] = colour;
			
			if (idx >= 1)
			{
				z_buf[idx - 1][idy] = z;
				c_buf[idx - 1][idy] = colour;
			}
			if (idy >= 1)
			{
				z_buf[idx][idy - 1] = z;
				c_buf[idx][idy - 1] = colour;
			}
		}
		
		x += dx;
		y += dy;
		z += dz;
	}
}

void ModelDrawer::draw_triangle(std::vector<Vertex> v, Vertex light_pos,
								QColor colour, bool outline)
{
	if (v[0].y() == v[1].y() && v[0].y() == v[2].y())
		return;
	
	if (v[0].y() > v[1].y())
		std::swap(v[0], v[1]);
	
	if (v[0].y() > v[2].y())
		std::swap(v[0], v[2]);
	
	if (v[1].y() > v[2].y())
		std::swap(v[1], v[2]);
	
	Vertex v_zero(0, 0, 0);
	MathVector vec[] = { MathVector(v_zero, v[0]),
						 MathVector(v_zero, v[1]),
						 MathVector(v_zero, v[2]) };
	
	MathVector l(v_zero, light_pos);
	MathVector n = (vec[2] - vec[0]) * (vec[1] - vec[0]);
	n.normalize();
	l.normalize();
	double intensity = n & l;
	
	if (intensity <= 0)
		return;
	
	int r = colour.red() * intensity;
	int g = colour.green() * intensity;
	int b = (colour.blue() * intensity);
	
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
			
	QColor c(r, g, b);
	
	double dy_0_2 = v[2].y() - v[0].y();
	double dy_0_1 = v[1].y() - v[0].y();
	double dy_1_2 = v[2].y() - v[1].y();
	
	for (int i = 0; i < int(round(dy_0_2)); i++)
	{
		bool second_half = (i > dy_0_1) || (v[1].y() == v[0].y());
		double seg_height = second_half ? dy_1_2 : dy_0_1;
		
		double alpha = i / dy_0_2;
		double beta = 1.0;
		if (second_half)
			beta = (i - dy_0_1) / seg_height;
		else
			beta = i / seg_height;
		
		MathVector A = vec[0] + alpha * (vec[2] - vec[0]);
		MathVector B;
		if (second_half)
			B = vec[1] + beta * (vec[2] - vec[1]);
		else
			B = vec[0] + beta * (vec[1] - vec[0]);
		
		if (A.x() > B.x())
			std::swap(A, B);
		
		for (int j = A.x(); j <= B.x(); j++)
		{
			double phi = 1.0;
			if (B.x() != A.x())
				phi = (j - A.x()) / (B.x() - A.x());
			
			MathVector P = A + phi * (B - A);
			int idx = int(round(P.x()));
			int idy = int(round(P.y()));
			
			if (idx >= 0 && idx < IMG_SIZE && idy >= 0 && idy < IMG_SIZE &&
					z_buf[idx][idy] < P.z())
			{
				z_buf[idx][idy] = int(P.z());
				c_buf[idx][idy] = c;
			}
		}
	}
	
	if (outline)
	{
		c = c.darker(120);
		draw_edge(v[0], v[1], c);
		draw_edge(v[1], v[2], c);
		draw_edge(v[0], v[2], c);
	}
}

void ModelDrawer::draw_scene(std::vector<Model> models, Camera& cam)
{
	QImage &img = canvas->get_image();
    QColor bg_color(0, 0, 0);
	img.fill(bg_color);
	
	if (models.size() == 0)
		return;
	
    for (int i = 0; i < IMG_SIZE; i++)
	{
        for (int j = 0; j < IMG_SIZE; j++)
        {
            z_buf[i][j] = -INT_MAX;
            c_buf[i][j] = bg_color;
        }
	}
	
	Vertex light_pos = light;
	
	light_pos.shift(cam.get_shift_params());
	light_pos.scale(cam.get_scale_params(), cam.get_center());
	light_pos.rotate(cam.get_rotate_params(), cam.get_center());
	
	light_pos.shift(IMG_SIZE / 2, IMG_SIZE / 2, 0);

    for (auto model : models)
    {
		std::vector<Vertex>& vertices = model.get_vertices();
		std::vector<Triangle> triangles = model.get_triangles();
		
		for (size_t i = 0; i < vertices.size(); i++)
			vertices[i].shift(IMG_SIZE / 2, IMG_SIZE / 2, 0);
		
		for (auto tr : triangles)
		{
			std::vector<Vertex> tr_vertices = tr.get_vertices(vertices);
			draw_triangle(tr_vertices, light_pos, tr.get_color());
		}
    }
	
	for (size_t i = 0; i < IMG_SIZE; i++)
        for (size_t j = 0; j < IMG_SIZE; j++)
            img.setPixelColor(i, j, c_buf[i][j].rgb());
	
	canvas->repaint();
}
