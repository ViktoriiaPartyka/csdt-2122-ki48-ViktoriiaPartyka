#ifndef MYSERVER_H
#define MYSERVER_H

// secondary libraries
#include <QDebug>
#include <QList>
#include <QObject>
// server stuff
#include <QTcpServer>
#include <QTcpSocket>
// JSON
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
// SQL
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class myServer : public QTcpServer
{
    Q_OBJECT
public:
    myServer();
    ~myServer();
    void startServer();

private:
    QString errStrMsg;
    QByteArray recievedData;
    QList<QTcpSocket*>* connectedClients;
    QJsonDocument* jsnDoc;
    QJsonParseError* errJsn = new QJsonParseError();
    QJsonObject* obj;
    QSqlDatabase* db;
    QSqlQuery* qry;
    void sendData(QTcpSocket* socket, QString& data);
    void decAndExec(QJsonDocument* doc, QTcpSocket* socket);
    void logProc(QTcpSocket* socket);
    void regProc(QTcpSocket* socket);
    void getCities(QTcpSocket* socket);
    void getTrainsList(QTcpSocket* socket);
    void getAvailableSeats(QTcpSocket* socket);
    void buyTicket(QTcpSocket* socket);
    void getUserTickets(QTcpSocket* socket);
    void buyReservedTicket(QTcpSocket* socket);
    void returnTicket(QTcpSocket* socket);
    QString createJsonStringFromQuery(QStringList& jsonFields, QSqlQuery* qry);

private slots:
    void incomingConnection(qintptr socketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif	// MYSERVER_H
