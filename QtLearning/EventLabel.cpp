#include "EventLabel.h"
#include <QMouseEvent>


EventLabel::EventLabel(QWidget* parent) : QLabel(parent)
{
}

static void _setText(QLabel* label, const QMouseEvent* event, const QString& action)
{
	label->setText(QString("<center><h1>%3: (%1, %2)</h1></center>")
			.arg(QString::number(event->x()),
				QString::number(event->y()),
				action));
}
void EventLabel::mouseMoveEvent(QMouseEvent* event)
{
	_setText(this, event, "Move");
}
void EventLabel::mousePressEvent(QMouseEvent* event)
{
	_setText(this, event, "Press");
}
void EventLabel::mouseReleaseEvent(QMouseEvent* event)
{
	_setText(this, event, "Release");
}
