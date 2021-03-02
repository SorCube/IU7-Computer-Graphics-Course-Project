#include <QTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workers/modelcreator.h"


#define CYL_TR_AMOUNT 50
#define RECT_NODE_AMOUNT_W 50
#define RECT_NODE_AMOUNT_H 10

#define FLAGPOLE_HEIGHT 400
#define FLAGPOLE_RAD 5

#define FLAG_WIDTH 200
#define FLAG_HEIGHT 100

#define BASE_SIZE 100

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
	  ui(new Ui::MainWindow),
	  flag(Vertex(0, 0, FLAGPOLE_HEIGHT - 10), FLAG_WIDTH, FLAG_HEIGHT,
		   QColor(180, 180, 255)),
	  is_animating(false)
{
	ui->setupUi(this);
	
	QObject::connect(ui->canvas, SIGNAL(shift_camera(std::vector<double>)),
					 this, SLOT(shift_camera(std::vector<double>)));
	QObject::connect(ui->canvas, SIGNAL(scale_camera(std::vector<double>)),
					 this, SLOT(scale_camera(std::vector<double>)));
	QObject::connect(ui->canvas, SIGNAL(rotate_camera(std::vector<double>)),
					 this, SLOT(rotate_camera(std::vector<double>)));
	
	CylinderCreator cr_cyl;
	facade.add_model(cr_cyl.create(Vertex(0, 0, 0), FLAGPOLE_RAD,
								   FLAGPOLE_HEIGHT,
								   CYL_TR_AMOUNT, QColor(255, 255, 255)));
	ParallelepipedCreator cr_par;
	facade.add_model(cr_par.create(Vertex(0, 0, 10),
								   BASE_SIZE, BASE_SIZE, BASE_SIZE / 5,
								   QColor(255, 255, 255)));
	
	facade.add_camera(Vertex(0, 0, 0));

	flag_ptr = flag.get_model();
	facade.add_model(flag_ptr);
	
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


void MainWindow::on_start_button_clicked()
{
    ui->start_button->setDisabled(true);
	ui->reset_button->setDisabled(true);
	is_animating = true;
	
	MathVector wv(ui->wind_box->value(), 0.1, 0);
	
	int msec = ui->msec_box->value();
	int shots = ui->shots_box->value();
	
	flag.set_mass(ui->mass_box->value());
	flag.set_friction(ui->fric_box->value());
	flag.set_spring(ui->spring_box->value());
	
	for (int i = 0; i < shots; i++)
	{
		flag.update(wv, msec);
		QTime end = QTime::currentTime().addMSecs(msec);
		while(QTime::currentTime() < end)
			QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
		*(flag_ptr) = *(flag.get_model());
		update_canvas();
	}
	
	ui->start_button->setEnabled(true);
	ui->reset_button->setEnabled(true);
	is_animating = false;
}

void MainWindow::on_reset_button_clicked()
{
	flag.reset();
	*(flag_ptr) = *(flag.get_model());
	update_canvas();
}
