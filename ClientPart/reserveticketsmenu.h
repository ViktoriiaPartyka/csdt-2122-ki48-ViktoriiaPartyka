#ifndef RESERVETICKETSMENU_H
#define RESERVETICKETSMENU_H

#include <QWidget>
#include <backend.h>
#include <QStandardItemModel>

namespace Ui
{
class reserveTicketsMenu;
}

class reserveTicketsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit reserveTicketsMenu(BackEnd* bckEnd, QWidget* parent = nullptr);
    ~reserveTicketsMenu();

private:
    Ui::reserveTicketsMenu* ui;
    BackEnd* bckEnd;
    QStandardItemModel* unActiveTicketsModel;
    QStandardItemModel* reservedTicketsModel;
    QStandardItemModel* boughtTicketsModel;
    QModelIndex reservedTicketIndex;
    void showBoughtTickets(QVariantList boughtTicketsList);
    void showReservedTickets(QVariantList reservedTicketsList);
    void showUnActiveTickets(QVariantList unActiveTicketsList);

private slots:
    void showUserTickets(QVariantList unActiveTickets, QVariantList boughtTickets, QVariantList reservedTickets);
    void reservedTicketTableClicked(const QModelIndex& index);
    void on_tabWidget_currentChanged(int index);
    void on_buyButton_clicked();
    void on_returnButton_clicked();
    void reservedTicketBought();
    void returnTicket();

signals:
    void _dataToSend(QByteArray);
};

#endif	// RESERVETICKETSMENU_H
