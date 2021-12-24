#ifndef WAGONBUTTON_H
#define WAGONBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QString>

class customButton : public QPushButton
{
   Q_OBJECT
public:
    int number;
    customButton(QWidget* parent);

signals:
    void cB_clicked(int wagonName);

protected slots:
    void slotForClick();
};

#endif	// WAGONBUTTON_H
