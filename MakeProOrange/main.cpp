#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "make.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if (!DoJob::InfoExists())
	{
		QMessageBox::information(nullptr, "Error", DoJob::GetAbsFile(INFO_FILE) + " is missing");
		return 0;
	}

	MainWindow w;
	w.show();

	return a.exec();
}
