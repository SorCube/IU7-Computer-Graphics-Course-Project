#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include <QMainWindow>
#include "drawer.h"
#include "canvas.h"
#include "facade/facade.h"
#include "flag/flag.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
	void update_canvas();
	
public slots:
	void shift_camera(std::vector<double> params);
	void scale_camera(std::vector<double> params);
	void rotate_camera(std::vector<double> params);
	
private slots:
	void on_start_button_clicked();
	
	void on_reset_button_clicked();
	
private:
	Ui::MainWindow *ui;
	
	static constexpr double offset = 10;
    static constexpr double scaleCoeff = 2;
    static constexpr double angle = 2 * M_PI / 180;

    Facade facade;
	Canvas* canvas;
	
	Flag flag;
	std::shared_ptr<Model> flag_ptr;
	
	bool is_animating;
};

#endif // MAINWINDOW_H
