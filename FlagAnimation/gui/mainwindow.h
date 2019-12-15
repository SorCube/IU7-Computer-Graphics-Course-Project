#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include <QMainWindow>
#include "drawer.h"
#include "../facade/facade.h"

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
	
protected:
	void keyPressEvent(QKeyEvent *event) override;
	virtual void wheelEvent(QWheelEvent *event) override;
	
private:
	Ui::MainWindow *ui;
	
	static constexpr double offset = 10;
    static constexpr double scaleCoeff = 2;
    static constexpr double angle = 2 * M_PI / 180;

    Facade facade;
	Canvas* canvas;
};

#endif // MAINWINDOW_H
