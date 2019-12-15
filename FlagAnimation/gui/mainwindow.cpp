#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../workers/modelcreator.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
	  ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	QObject::connect(ui->canvas, SIGNAL(rotate_camera(std::vector<double>)),
					 this, SLOT(rotate_camera(std::vector<double>)));
	
	double c = IMG_SIZE / 2;
	PlateCreator cr_plate;
	facade.add_model(cr_plate.create(Vertex(c, c, 0), 5000, 5000,
									 QColor(120, 180, 120)));
	
	CylinderCreator cr_cyl;
	facade.add_model(cr_cyl.create(Vertex(c, c, 0), 5, 400, 50,
								   QColor(255, 255, 255)));
	ParallelepipedCreator cr_par;
	facade.add_model(cr_par.create(Vertex(c, c, 10),
								   100, 100, 20, QColor(180, 180, 180)));
	
	facade.add_camera(Vertex(400, 400, 0));
	
	FlexRectCreator cr_flag;
	Model flag = cr_flag.create(Vertex(c + 105, c, 300), 200, 100, 10, 5,
								QColor(120, 120, 255));
	flag.rotate(M_PI / 2, 0, 0, Vertex(c, c, 300));
	facade.add_model(flag);
	
	Transformations::Rotation rt(-M_PI, 0, 0);
	CameraTransformator tr2(rt);
	facade.transform_camera(tr2, 0);
	
	update_canvas();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::update_canvas()
{
	ModelDrawer drawer(ui->canvas);
	facade.draw(drawer, 0);
}

void MainWindow::shift_camera(std::vector<double> params)
{
	Transformations::Shifting t(params[0], params[1], params[2]);
	CameraTransformator tr(t);
	facade.transform_camera(tr, 0);
	update_canvas();
}

void MainWindow::scale_camera(std::vector<double> params)
{
	Transformations::Scaling t(params[0], params[1], params[2]);
	CameraTransformator tr(t);
	facade.transform_camera(tr, 0);
	update_canvas();
}

void MainWindow::rotate_camera(std::vector<double> params)
{
	Transformations::Rotation t(params[0], params[1], params[2]);
	CameraTransformator tr(t);
	facade.transform_camera(tr, 0);
	update_canvas();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_A)
		shift_camera({-10, 0, 0});
	if (event->key() == Qt::Key_D)
		shift_camera({10, 0, 0});
	if (event->key() == Qt::Key_W)
		shift_camera({0, -10, 0});
	if (event->key() == Qt::Key_S)
		shift_camera({0, 10, 0});
	if (event->key() == Qt::Key_Q)
		shift_camera({0, 0, -10});
	if (event->key() == Qt::Key_E)
		shift_camera({0, 0, 10});
	
	if (event->key() == Qt::Key_R)
		rotate_camera({-0.05, 0, 0});
	if (event->key() == Qt::Key_F)
		rotate_camera({0.05, 0, 0});
	if (event->key() == Qt::Key_T)
		rotate_camera({0, -0.05, 0});
	if (event->key() == Qt::Key_G)
		rotate_camera({0, 0.05, 0});
	if (event->key() == Qt::Key_Y)
		rotate_camera({0, 0, -0.05});
	if (event->key() == Qt::Key_H)
		rotate_camera({0, 0, 0.05});
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
		scale_camera({1.1, 1.1, 1.1});
    else
		scale_camera({0.9, 0.9, 0.9});
}

