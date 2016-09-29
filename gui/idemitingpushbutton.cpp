#include "idemitingpushbutton.h"

IdEmitingPushButton::IdEmitingPushButton(int id, const QString &text, QWidget *parent) :
    QPushButton(text, parent)
{
    this->id = id;
    connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClick(bool)));
}

IdEmitingPushButton::IdEmitingPushButton(int id, const QString &text, const QIcon &icon,  QWidget *parent) :
    QPushButton(icon, text, parent)
{
    this->id = id;
    connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClick(bool)));
}

IdEmitingPushButton::~IdEmitingPushButton() {

}

//slots
void IdEmitingPushButton::buttonClick(bool checked) {
    emit clicked_id(id);
}
