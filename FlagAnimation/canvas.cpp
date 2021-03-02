#include "canvas.h"
#include <iostream>

Canvas::Canvas(QWidget *parent) :
	QWidget(parent),
	painter()
{
	img = QImage(IMG_SIZE, IMG_SIZE, QImage::Format_RGB32);
	setMouseTracking(true);
	setFocusPolicy(Qt::ClickFocus);
}

void Canvas::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	painter.begin(this);
	painter.drawImage(0, 0, img);
	painter.end();
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_A)
		emit shift_camera({-10, 0, 0});
	if (event->key() == Qt::Key_D)
		emit shift_camera({10, 0, 0});
	if (event->key() == Qt::Key_W)
		emit shift_camera({0, -10, 0});
	if (event->key() == Qt::Key_S)
		emit shift_camera({0, 10, 0});
	if (event->key() == Qt::Key_Q)
		emit shift_camera({0, 0, -10});
	if (event->key() == Qt::Key_E)
		emit shift_camera({0, 0, 10});
	
	if (event->key() == Qt::Key_R)
		emit rotate_camera({-0.05, 0, 0});
	if (event->key() == Qt::Key_F)
		emit rotate_camera({0.05, 0, 0});
	if (event->key() == Qt::Key_T)
		emit rotate_camera({0, -0.05, 0});
	if (event->key() == Qt::Key_G)
		emit rotate_camera({0, 0.05, 0});
	if (event->key() == Qt::Key_Y)
		emit rotate_camera({0, 0, -0.05});
	if (event->key() == Qt::Key_H)
		emit rotate_camera({0, 0, 0.05});
}

void Canvas::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0)
		emit scale_camera({1.1, 1.1, 1.1});
	else
		emit scale_camera({0.9, 0.9, 0.9});
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
	if (!event->buttons().testFlag(Qt::RightButton))
        return;

    if (prev_x == -1 && prev_y == -1)
    {
        prev_x = event->screenPos().x();
        prev_y = event->screenPos().y();
        return;
    }

    std::vector<double> r = {0, 0, 0};
    int x = event->screenPos().x() - prev_x;
    int y = event->screenPos().y() - prev_y;

    if (abs(x) >= abs(y))
    {
        if (x > 0)
            r[1] = 0.05;
        else
            r[1] = -0.05;
    }
    else
    {
        if (y > 0)
            r[0] = 0.05;
        else
            r[0] = -0.05;
    }

    prev_x = event->screenPos().x();
    prev_y = event->screenPos().y();

    emit rotate_camera(r);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton)
        return;

    /*pair <int, int> p;
    p.first = event->scenePos().x();
    p.second = event->scenePos().y();

    emit checkInside(p);*/
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event)

    prev_x = -1;
    prev_y = -1;
}

QPainter& Canvas::get_painter()
{
	return painter;
}

QImage& Canvas::get_image()
{
	return img;
}

void Canvas::draw_start()
{
	painter.begin(&img);
}

void Canvas::draw_end()
{
	painter.end();
	repaint();
}

void Canvas::draw_point(double x, double y, QColor c)
{
	painter.setPen(c);
	painter.drawPoint(x, y);
}

void Canvas::draw_line(double x1, double y1, double x2, double y2, QColor c)
{
	painter.setPen(c);
	painter.drawLine(x1, y1, x2, y2);
}
