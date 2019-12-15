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

    light = Vertex(IMG_SIZE / 4, IMG_SIZE / 2, IMG_SIZE / 4);

    screen = new int*[IMG_SIZE];
    shadow = new int*[IMG_SIZE];
    transformedShadow = new bool*[IMG_SIZE];
    buffer = new QColor*[IMG_SIZE];
	
	z_buf = new int*[IMG_SIZE];

    for (int i = 0; i < IMG_SIZE; ++i)
    {
        screen[i] = new int[IMG_SIZE];
        shadow[i] = new int[IMG_SIZE];
        transformedShadow[i] = new bool[IMG_SIZE];
        buffer[i] = new QColor[IMG_SIZE];
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
				z < screen[int(x)][int(y)])
		{
			screen[idx][idy] = z;
			buffer[idx][idy] = colour;
			
			if (idx >= 1)
			{
				screen[idx - 1][idy] = z;
				buffer[idx - 1][idy] = colour;
			}
			if (idy >= 1)
			{
				screen[idx][idy - 1] = z;
				buffer[idx][idy - 1] = colour;
			}
		}
		
		x += dx;
		y += dy;
		z += dz;
	}
}

void ModelDrawer::draw_triangle(std::vector<Vertex> v, Vertex& cam_pos,
								Vertex& light_pos, QColor colour)
{
	/*if (v[0].y() == v[1].y() && v[0].y() == v[2].y())
		return;
	
	if (v[0].y() > v[1].y())
		std::swap(v[0], v[1]);
	
	if (v[0].y() > v[2].y())
		std::swap(v[0], v[2]);
	
	if (v[1].y() > v[2].y())
		std::swap(v[1], v[2]);
	
	double dy_0_2 = v[2].y() - v[0].y();
	double dy_0_1 = v[1].y() - v[0].y();
	double dy_1_2 = v[2].y() - v[1].y();
	
	Vertex v_zero(0, 0, 0);
	MathVector vec[] = { MathVector(v[0], v_zero),
						 MathVector(v[1], v_zero),
						 MathVector(v[2], v_zero) };
	
	for (int i = 0; i < int(dy_0_2); i++)
	{
		bool second_half = (i > v[1].y() - v[0].y()) || (v[1].y() == v[0].y());
		double seg_height = second_half ? dy_1_2 : dy_0_1;
		
		double alpha = i / dy_0_2;
		double beta = (i-(second_half ? dy_0_1 : 0)) / seg_height; 
		
		MathVector A = vec[0] + (vec[2] - vec[1]) * alpha;
		MathVector B;
		if (second_half)
			B = vec[1] + (vec[2] - vec[1]) * beta;
		else
			B = vec[0] + (vec[1] - vec[0]) * beta;
		
		if (A.x() > B.x())
			std::swap(A, B);
		
		for (int j = A.x(); j <= B.x(); j++)
		{
			double phi = 1.0;
			if (B.x() != A.x())
				phi = (j - A.x()) / (B.x() - A.x());
			
			MathVector P = A + (B - A) * phi;
			int idx = int(P.x());
			int idy = int(P.y());
			if (z_buf[idx][idy] < P.z())
			{
				z_buf[idx][idy] = int(P.z());
				buffer[idx][idy] = colour;
			}
		}
	}*/
	
	MathVector n = MathVector(v[1], v[2]) * MathVector(v[1], v[0]);
    MathVector l(v[0], light_pos);
	MathVector h(v[0], cam_pos);

    int r, g, b;
    colour.getRgb(&r, &g, &b);

    n.normalize();
    l.normalize();
    h.normalize();

    double K1, K2;

    K1 = n & l;
    K2 = n & h;

    while (abs(K1) < 100 && abs(K2) < 100)
    {
        K1 *= 10;
        K2 *= 10;
    }

    K1 /= 10;
    K2 /= 10;

    if (r)
        r = (int)(0.8 * r + 0.8 * K1 + 0.65 * K2);
    if (g)
        g = (int)(0.8 * g + 0.8 * K1 + 0.65 * K2);
    if (b)
        b = (int)(0.8 * b + 0.8 * K1 + 0.65 * K2);

    if (r > 255)
		r = 255;
    if (g > 255)
		g = 255;
    if (b > 255)
		b = 255;

    if (r < 0)
		r = 0;
    if (g < 0)
		g = 0;
    if (b < 0)
		b = 0;

    QColor c(r, g, b);

    int size = v.size();
	int *x = new int[v.size()];
	int *y = new int[v.size()];

    for (int i = 0; i < size; i++)
	{
        x[i] = int(v[i].x());
		y[i] = int(v[i].y());
	}

    int ymax = y[0], ymin = y[0];
    for (int i = 1; i < size; i++)
    {
        ymax = std::max(ymax, y[i]);
        ymin = std::min(ymin, y[i]);
    }

    ymin = (ymin < 0) ? 0 : ymin;
    ymax = (ymax < 2000) ? ymax : 2000;

    int ne, e;
    int x1, x2;
    double z1, z2, tc, z;

    for (int ysc = ymin; ysc < ymax; ysc++)
    {
        ne = 0;
        for (int e = 0; e < size; e++)
        {
            int e1 = e + 1;
            if (e1 == size)
				e1 = 0;
			
            if (y[e] < y[e1])
            {
                if (y[e1] <= ysc || ysc < y[e])
					continue;
            }
            else if (y[e] > y[e1])
            {
                if (y[e1] > ysc || ysc >= y[e])
					continue;
            }
            else
				continue;

            tc = double(y[e] - ysc) / (y[e] - y[e1]);
            if (ne)
            {
                x2 = x[e] + int (tc * (x[e1] - x[e]));
                z2 = v[e].z() + tc * (v[e1].z() - v[e].z());
            }
            else
            {
                x1 = x[e] + int (tc * (x[e1] - x[e]));
                z1 = v[e].z() + tc * (v[e1].z() - v[e].z());
                ne = 1;
            }
        }

        if (x2 < x1)
        {
            e = x1;
            x1 = x2;
            x2 = e;
            tc = z1;
            z1 = z2;
            z2 = tc;
        }

        int xsc1 = (x1 < 0) ? 0 : x1;
        int xsc2 = (x2 < IMG_SIZE) ? x2 : IMG_SIZE;

        for (int xsc = xsc1; xsc < xsc2; xsc++)
        {
            tc = double(x1 - xsc) / (x1 - x2);
            z = z1 + tc * (z2 - z1);

			if (xsc >= 0 && xsc < IMG_SIZE && ysc > 0 && ysc < IMG_SIZE &&
					z < screen[xsc][ysc])
            {
                buffer[xsc][ysc] = c;
                screen[xsc][ysc] = z;
            }
        }
    }
	
	delete [] x;
	delete [] y;
}

void ModelDrawer::draw_scene(std::vector<Model> models, Camera& cam)
{
	QImage &img = canvas->get_image();
    QColor bg_color(224, 255, 255);
	img.fill(bg_color);
	
	if (models.size() == 0)
		return;
	
    for (int i = 0; i < IMG_SIZE; i++)
	{
        for (int j = 0; j < IMG_SIZE; j++)
        {
            screen[i][j] = INT_MAX;
            shadow[i][j] = -INT_MAX;
            transformedShadow[i][j] = true;
            buffer[i][j] = bg_color;
        }
	}
	
	Vertex cam_pos = cam.get_pos();
	std::vector<double> inv_shift = cam.get_inv_shift_params();
	std::vector<double> inv_scale = cam.get_inv_scale_params();
	std::vector<double> inv_rotate = cam.get_inv_rotate_params();
	
	cam_pos.shift(cam.get_inv_shift_params());
	cam_pos.scale(cam.get_inv_scale_params(), cam.get_center());
	cam_pos.rotate(cam.get_inv_rotate_params(), cam.get_center());
	
	Vertex light_pos = light;
	
	light_pos.shift(cam.get_shift_params());
	light_pos.scale(cam.get_inv_scale_params(), cam.get_center());
	light_pos.rotate(cam.get_inv_rotate_params(), cam.get_center());

    for (auto model : models)
    {
		std::vector<Vertex>& vertices = model.get_vertices();
		/*std::vector<Triangle> vis_sides = model.get_visible_sides(cam);
		for (auto tr : vis_sides)
		{
			std::vector<Vertex> tr_vertices = tr.get_vertices(vertices);
			draw_triangle(tr_vertices, cam_pos, light_pos, tr.get_color());
		}*/
		std::vector<Triangle> triangles = model.get_triangles();
		for (auto tr : triangles)
		{
			std::vector<Vertex> tr_vertices = tr.get_vertices(vertices);
			draw_triangle(tr_vertices, cam_pos, light_pos, tr.get_color());
			
			QColor c = tr.get_color().darker(120);
			draw_edge(tr_vertices[0], tr_vertices[1], c);
			draw_edge(tr_vertices[1], tr_vertices[2], c);
			draw_edge(tr_vertices[0], tr_vertices[2], c);
		}
    }
	
	for (size_t i = 0; i < IMG_SIZE; i++)
	{
        for (size_t j = 0; j < IMG_SIZE; j++)
        {
            /*if (transformedShadow[j][i] && screen[j][i] != INT_MAX)
                buffer[j][i] = buffer[j][i].darker(120);*/
            img.setPixelColor(i, j, buffer[i][j].rgb());
        }
	}
	canvas->repaint();
}
