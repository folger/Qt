#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QGroupBox>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QGroupBox* PlatformGroup();
	QGroupBox* FuncsGroup();

	std::vector<QCheckBox*> checkFuncs_;
	QCheckBox* checkWin32_;
	QCheckBox* checkX64_;
};

#endif // MAINWINDOW_H
