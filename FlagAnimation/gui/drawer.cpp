#include <thread>
#include <algorithm>
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

    light = Vertex(5000, 5000, 5000);

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

void ModelDrawer::draw_triangle(std::vector<Vertex> v,
								std::vector<MathVector> n,
								MathVector l, QColor colour, bool outline)
{
	if (v[0].y() == v[1].y() && v[0].y() == v[2].y())
		return;
	
	double intens[3];
	for (int i = 0; i < 3; i++)
		intens[i] = abs(n[i] & l);
	
	if (v[0].y() > v[1].y())
	{
		std::swap(v[0], v[1]);
		std::swap(intens[0], intens[1]);
	}
	
	if (v[0].y() > v[2].y())
	{
		std::swap(v[0], v[2]);
		std::swap(intens[0], intens[2]);
	}
	
	if (v[1].y() > v[2].y())
	{
		std::swap(v[1], v[2]);
		std::swap(intens[1], intens[2]);
	}
	
	Vertex v_zero(0, 0, 0);
	MathVector vec[] = { MathVector(v_zero, v[0]),
						 MathVector(v_zero, v[1]),
						 MathVector(v_zero, v[2]) };
	
	double dy_0_2 = v[2].y() - v[0].y();
	double dy_0_1 = v[1].y() - v[0].y();
	double dy_1_2 = v[2].y() - v[1].y();
	
	double ia_0 = intens[0] / dy_0_1;
	double ia_1 = intens[1] / dy_0_1;
	double ib_0 = intens[0] / dy_0_2;
	double ib_2 = intens[2] / dy_0_2;
	
	for (int i = 0; i < dy_0_2; i++)
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
		
		double dx = B.x() - A.x();
		double ddx = (dx == 0) ? 0.0 : 1 / dx;
		double ia = (dx == 0) ? 0.0 : (ia_0 * (v[1].y() - A.y()) +
									   ia_1 * (A.y() - v[0].y())) / dx;
		double ib = (dx == 0) ? 0.0 : (ib_0 * (v[2].y() - B.y()) +
									   ib_2 * (B.y() - v[0].y())) / dx;
		
		for (int x = 0; x <= dx; x++)
		{
			MathVector P = A + x * ddx * (B - A);
			double intens_p = ia * (B.x() - P.x()) + ib * (P.x() - A.x());
			
			int idx = round(P.x());
			int idy = round(P.y());
			
			if (idx >= 0 && idx < IMG_SIZE && idy >= 0 && idy < IMG_SIZE &&
					z_buf[idx][idy] < P.z())
			{
				z_buf[idx][idy] = int(round(P.z()));
				
				int r = round(colour.red() * abs(intens_p));
				int g = round(colour.green() * abs(intens_p));
				int b = round(colour.blue() * abs(intens_p));
				
				if (r > 255)
					r = 255;
				if (g > 255)
					g = 255;
				if (b > 255)
					b = 255;
				
				c_buf[idx][idy] = QColor(r, g, b);
			}
		}
	}
	
	if (outline)
	{
		colour = colour.darker(120);
		draw_edge(v[0], v[1], colour);
		draw_edge(v[1], v[2], colour);
		draw_edge(v[0], v[2], colour);
	}
}

void ModelDrawer::draw_scene(std::vector<Model> models, Camera& cam)
{
	QImage &img = canvas->get_image();
    QColor bg_color(180, 240, 240);
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
	
	light_pos.shift(canv_shift);
	light_pos.rotate(canv_rotate, canv_center);
	
	std::vector<double>& params = cam.get_rotate_params();
	
	Vertex v0(0, 0, 0);
	
	v0.shift(cam.get_shift_params());
	v0.scale(cam.get_scale_params(), cam.get_center());
	v0.rotate(cam.get_rotate_params(), cam.get_center());
	
	v0.shift(canv_shift);
	v0.rotate(canv_rotate, canv_center);
	
	MathVector l(v0, light_pos);
	l.normalize();

    for (auto model : models)
    {
		std::vector<Vertex>& vertices = model.get_vertices();
		std::vector<Triangle>& triangles = model.get_triangles();
		
		for (size_t i = 0; i < vertices.size(); i++)
		{
			vertices[i].shift(canv_shift);
			vertices[i].rotate(canv_rotate, canv_center);
		}
		
		std::vector<MathVector> normals = model.get_normals();
		
		for (auto tr : triangles)
		{
			std::vector<Vertex> v = tr.get_vertices(vertices);
			std::vector<MathVector> n = tr.get_normals(normals);
			draw_triangle(v, n, l, tr.get_color());
		}
    }
	
	size_t di = IMG_SIZE / 4, i = 0;
	
	std::vector<std::thread> threads;
	for (size_t k = 0; k < 4; k++, i += di)
		threads.push_back(std::thread(ModelDrawer::fill_buffer,
									  this, std::ref(img), i, i + di));
	
	for (size_t k = 0; k < 4; k++)
		threads[k].join();
	
	canvas->repaint();
}

void ModelDrawer::fill_buffer(QImage& img, size_t start, size_t end)
{
	for (size_t i = start; i < end; i++)
		for (size_t j = 0; j < IMG_SIZE; j++)
			img.setPixelColor(i, j, c_buf[i][j].rgb());
}
