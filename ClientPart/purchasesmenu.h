#ifndef PURCHASESMENU_H
#define PURCHASESMENU_H

#include <QWidget>
#include <buytickets.h>
#include <reserveticketsmenu.h>
#include <backend.h>

namespace Ui
{
class PurchasesMenu;
}

class PurchasesMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PurchasesMenu(BackEnd* bckEnd, QWidget* parent = nullptr);
    ~PurchasesMenu();
    bool eventFilter(QObject* watched, QEvent* event);	// for handling on button click event

private:
    Ui::PurchasesMenu* ui;
    BuyTickets* BuyScreen;
    reserveTicketsMenu* reserveScreen;
    BackEnd* bckEnd;
    void setShadowEff();
    void setIcons();											// set icons on start of ui
    void setEnterIcon(QObject* watched);	// set new icon when mouse enter button
    void setLeaveIcon(QObject* watched);	// set new icon when mouse leave button
    void showTicketsForCurrentUser();

private slots:
    void on_BuyButton_clicked();
    void on_ReserveButton_clicked();
    void on_LogOutButton_clicked();
    void on_exitButton_clicked();
    void on_logOutButton_clicked();

signals:
    void _dataToSend(QByteArray dataToSend);
    void _closeApp();
    void _logOut();

};

#endif	// PURCHASESMENU_H
