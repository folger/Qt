#ifndef NEWSPAPER_H
#define NEWSPAPER_H

#include <QObject>

class Newspaper : public QObject
{
	Q_OBJECT
public:
	Newspaper(const QString& name) : name_(name) {}
    void send()
	{
        emit newPaper(name_);
	}

signals:
	void newPaper(const QString& name);

private:
	QString name_;
};

#endif // NEWSPAPER_H

