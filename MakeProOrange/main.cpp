#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "make.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if (!DoJob::InfoExists())
	{
		QMessageBox::information(nullptr, "Error", QString(INFO_FILE) + " is missing from current folder");
		return 0;
	}

    MainWindow w;
    w.show();

    return a.exec();
}
