#pragma once
#ifndef BACKEND_H
#define BACKEND_H

#include <QMessageBox>
#include <QObject>
#include <QWhatsThis>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPushButton>
#include <QFile>

class BackEnd : public QObject
{
    Q_OBJECT
public:
    explicit BackEnd(QObject* parent = nullptr);
    ~BackEnd();
    void setCurUsername(QString userName);
    QString getCurUserame();
    void showErrorMsg(QWidget* widget, QString errMsg);

private:
    QTcpSocket* socket;
    QByteArray recievedData;
    QJsonDocument* jsnDoc;
    QJsonParseError* errJsn;
    QJsonObject* obj;
    QString curUsername;
    void decAndExec();
    void logProc();
    void regProc();
    void cListProc();
    void trainsListProc();
    void getAvailableSeats();
    void buyTicket();
    void getUserTickets();
    void buyReservedTicket();
    void returnTicket();

private slots:
    void createSocket();
    void sendData(QByteArray dataToSend);
    void sockReady();
    void tryToReccon();
    void sockDisc();

signals:
    void _reconnFailed();
    void _reconnSuccess();
    void _logSuccess();
    void _regSuccess();
    void _errSignalMW(QString info);
    void _cList(QStringList cList);
    void _trainsList(QVariantList trainsList);
    void _availableSeats(QString wagonsCounr, QStringList trainsList);
    void _ticketPurchaseSuccess();
    void _userTickets(QVariantList unActiveTickets, QVariantList boughtTickets, QVariantList reservedTickets);
    void _ticketAlreadyTaken();
    void _reservedTicketBought();
    void _returnTicket();
};

#endif
