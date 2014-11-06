#include <QVBoxLayout>
#include "mainwindow.h"
#include "make.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Pro Orange");

	DoJob dojob;
	std::vector<QString> funcnames;
	dojob.GetFuncNames(funcnames);

	for (auto& name : funcnames)
	{
		checkFuncs_.push_back(new QCheckBox(name));	
	}

	auto layout = new QVBoxLayout();
	for (auto check : checkFuncs_)
	{
		layout->addWidget(check);
	}

	QWidget *window = new QWidget();
	window->setLayout(layout);
	setCentralWidget(window);
}

MainWindow::~MainWindow()
{

}
