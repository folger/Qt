#include "mainwindow.h"
#include "UserAgeDialog.h"
#include "EventLabel.h"
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
	setWindowTitle(tr("Folger's first Qt Window"));

	openAction_ = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
	openAction_->setShortcuts(QKeySequence::Open);
	openAction_->setStatusTip(tr("Open an existing file"));
	connect(openAction_, &QAction::triggered, this, &MainWindow::open);

	auto msgBoxAction = new QAction(tr("Test Message Box..."), this);
	connect(msgBoxAction, &QAction::triggered, this, &MainWindow::msgbox);

	QMenu* file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction_);
	file->addAction(msgBoxAction);

	QToolBar* toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction_);

	statusBar()->addAction(openAction_);

	auto label = new EventLabel(this);
	label->setText("MouseEvent demo");
	label->setMouseTracking(true);

	auto layout = new QVBoxLayout;
	layout->addWidget(label);

	setCentralWidget(new QWidget);
	centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::open()
{
	UserAgeDialog dialog(this);
	auto ret = dialog.exec();
	if (ret == QDialog::Accepted)
	{
		qDebug() << dialog.getAge();
	}
}

void MainWindow::msgbox()
{
	QMessageBox msgBox;
	msgBox.setText(tr("The document has been modified."));
	msgBox.setInformativeText(tr("Do you want to save your changes?"));
	msgBox.setDetailedText(tr("Differences are here ..."));
	msgBox.setStandardButtons(QMessageBox::Save |
			QMessageBox::Discard |
			QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();
	switch (ret)
	{
		case QMessageBox::Save:
			qDebug() << "Save document!";
			break;
		case QMessageBox::Discard:
			qDebug() << "Discard document!";
			break;
		case QMessageBox::Cancel:
			qDebug() << "Close document!";
			break;
		default:
			break;
	}
}
