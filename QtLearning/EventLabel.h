#ifndef __EVENT_LABEL__
#define __EVENT_LABEL__

#include <QLabel>
class EventLabel : public QLabel
{
	Q_OBJECT
public:
	EventLabel(QWidget* parent);

protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif /// __EVENT_LABEL__
