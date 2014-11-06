#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "mainwindow.h"
#include "make.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle("Pro Orange");

	auto layout = new QVBoxLayout();
	layout->addWidget(PlatformGroup());
	layout->addWidget(FuncsGroup());
	auto btnDo = new QPushButton("Do");
	layout->addWidget(btnDo);

	setCentralWidget(new QWidget);
	centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{

}

QGroupBox* MainWindow::PlatformGroup()
{
	auto layout = new QHBoxLayout();
	checkWin32_ = new QCheckBox("Win32");
	checkX64_ = new QCheckBox("x64");
	layout->addWidget(checkWin32_);
	layout->addWidget(checkX64_);
	
    auto group = new QGroupBox("Platform");
	group->setLayout(layout);
	return group;
}

QGroupBox* MainWindow::FuncsGroup()
{
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

	auto group = new QGroupBox("Functions");
	group->setLayout(layout);
	return group;
}
