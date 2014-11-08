#include "UserAgeDialog.h"
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

UserAgeDialog::UserAgeDialog(QWidget* parent) : QDialog(parent), age_(0)
{
	setWindowTitle(tr("Set User Age"));

	auto layout = new QVBoxLayout;
	layout->addLayout(ageLayout());
	layout->addLayout(buttonLayout());
	setLayout(layout);
}
UserAgeDialog::~UserAgeDialog()
{
}
QLayout* UserAgeDialog::ageLayout()
{
	auto spinBox = new QSpinBox(this);
	auto slider = new QSlider(Qt::Horizontal, this);
	spinBox->setRange(0, 130);
	slider->setRange(0, 130);

	connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
	void (QSpinBox::*spinBoxValueChanged)(int) = &QSpinBox::valueChanged;
	connect(spinBox, spinBoxValueChanged, slider, &QSlider::setValue);
	connect(spinBox, spinBoxValueChanged, this, &UserAgeDialog::setAge);
	spinBox->setValue(35);

	auto layout = new QHBoxLayout;
	layout->addWidget(spinBox);
	layout->addWidget(slider);
	return layout;
}
QLayout* UserAgeDialog::buttonLayout()
{
	auto btnOK = new QPushButton(tr("OK"), this);
	auto btnCancel = new QPushButton(tr("Cancel"), this);
	restricButtonWidth(btnOK);
	restricButtonWidth(btnCancel);

	connect(btnOK, &QPushButton::clicked, this, &QDialog::accept);
	connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);

	auto layout = new QHBoxLayout;
	layout->addStretch();
	layout->addWidget(btnOK);
	layout->addWidget(btnCancel);
	return layout;
}
void UserAgeDialog::restricButtonWidth(QPushButton* btn)
{
    btn->setFixedWidth(70);
}
