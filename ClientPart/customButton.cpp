#include "customButton.h"

customButton::customButton(QWidget* parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(slotForClick()));
}

void customButton::slotForClick()
{
    emit this->cB_clicked(number);
}
