#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T09:47:03
#
#-------------------------------------------------

QT	   += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtLearning
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp\
		UserAgeDialog.cpp

HEADERS  += mainwindow.h\
		UserAgeDialog.h

FORMS	+=

RESOURCES += \
	general.qrc

CONFIG += c++11
