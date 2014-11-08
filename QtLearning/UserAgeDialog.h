#ifndef __USRE_AGE_DIALOG__
#define __USRE_AGE_DIALOG__

#include <QDialog>
class UserAgeDialog : public QDialog
{
	Q_OBJECT
public:
	UserAgeDialog(QWidget* parent);
	~UserAgeDialog();
	int getAge() {return age_;}

private:
	QLayout* ageLayout();
	QLayout* buttonLayout();
	void restricButtonWidth(QPushButton* btn);
	void setAge(int age) {age_ = age;}
	int age_;
};
#endif /// __USRE_AGE_DIALOG__

