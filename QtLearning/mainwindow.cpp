#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
	setWindowTitle(tr("Folger's first Qt Window"));

	openAction_ = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
	openAction_->setShortcuts(QKeySequence::Open);
	openAction_->setStatusTip(tr("Open an existing file"));
	connect(openAction_, &QAction::triggered, this, &MainWindow::open);

	QMenu* file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction_);

	QToolBar* toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction_);

	statusBar()->addAction(openAction_);
}

MainWindow::~MainWindow()
{
}

void MainWindow::open()
{
	QMessageBox::information(this, tr("Information"), tr("Open"));
}
