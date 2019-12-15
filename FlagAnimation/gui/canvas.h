#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <vector>

#define IMG_SIZE 800

class Canvas : public QWidget
{
	Q_OBJECT
public:
	explicit Canvas(QWidget *parent = nullptr);
	
	QPainter& get_painter();
	QImage& get_image();
	
	void draw_start();
	void draw_end();
	
	void draw_point(double x, double y, QColor c);
	void draw_line(double x1, double y1, double x2, double y2, QColor c);
	
	
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	
private:
	QImage img;
	QPainter painter;
	int prev_x, prev_y;
	
signals:
	void rotate_camera(std::vector<double> param);
	
public slots:
};

#endif // CANVAS_H
