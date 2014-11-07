#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "mainwindow.h"
#include "make.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), doJob_(std::make_shared<DoJob>())
{
	setWindowTitle("Pro Orange");

	auto layout = new QVBoxLayout();
	layout->addWidget(PlatformGroup());
	layout->addWidget(FuncsGroup());
	auto btnDo = new QPushButton("Do");
	connect(btnDo, &QPushButton::clicked, this, &MainWindow::Do);
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
	radioWin32_ = new QRadioButton("Win32");
	radioX64_ = new QRadioButton("x64");
	radioWin32_->setChecked(true);
	layout->addWidget(radioWin32_);
	layout->addWidget(radioX64_);
	
    auto group = new QGroupBox("Platform");
	group->setLayout(layout);
	return group;
}

QGroupBox* MainWindow::FuncsGroup()
{
	std::vector<QString> funcnames;
	doJob_->GetFuncNames(funcnames);

	for (auto& name : funcnames)
	{
		auto check = new QCheckBox(name);
		check->setChecked(true);
		checkFuncs_.push_back(check);
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

void MainWindow::Do()
{
	doJob_->Do(radioX64_->isChecked(),
		[this](size_t index)
		{
			return checkFuncs_[index]->isChecked();
		}
	);
}
