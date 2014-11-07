#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>
#include <memory>

class DoJob;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QGroupBox* PlatformGroup();
	QGroupBox* FuncsGroup();

	void Do();

	std::vector<QCheckBox*> checkFuncs_;
	QRadioButton* radioWin32_;
	QRadioButton* radioX64_;

	std::shared_ptr<DoJob> doJob_;
};

#endif // MAINWINDOW_H
