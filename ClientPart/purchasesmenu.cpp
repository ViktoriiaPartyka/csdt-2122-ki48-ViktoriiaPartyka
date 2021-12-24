#include "purchasesmenu.h"
#include "ui_purchasesmenu.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <UiHelperPurchasesMenu.cpp>
#include <QPixmap>
#include <QEvent>

// constructor
PurchasesMenu::PurchasesMenu(BackEnd* bckEnd, QWidget* parent) : QWidget(parent), ui(new Ui::PurchasesMenu)
{
    ui->setupUi(this);

    // create pointer wich points to mainwindow bckEnd
    this->bckEnd = bckEnd;

    // adding BuyTickets screen to stacked widget
    BuyScreen = new BuyTickets(bckEnd);
    ui->stackedWidget->addWidget(BuyScreen);

    reserveScreen = new reserveTicketsMenu(bckEnd);
    ui->stackedWidget->addWidget(reserveScreen);

    // seting ButTickets as start screen
    ui->stackedWidget->setCurrentWidget(BuyScreen);

    // to be able to send data to bckEnd object
    connect(this, SIGNAL(_dataToSend(QByteArray)), bckEnd, SLOT(sendData(QByteArray)));

    // set icons on start of ui
    setIcons();

    ui->BuyButton->setCheckable(0);
    QPixmap BuyIcon(":/recources/img/TrainIconFocus.png");
    ui->BuyButton->setIcon(BuyIcon);

    setShadowEff();
}

// destructor
PurchasesMenu::~PurchasesMenu()
{
    delete ui;
}

// to handle on button click events
bool PurchasesMenu::eventFilter(QObject* watched, QEvent* event)
{
    QPushButton* button = qobject_cast<QPushButton*>(watched);

    if (!button)
    {
        return false;
    }

    if (event->type() == QEvent::HoverEnter)
    {
        setEnterIcon(watched);
        return true;
    }
    else if (event->type() == QEvent::HoverLeave)
    {
        setLeaveIcon(watched);
        return true;
    }

    return false;
}

void PurchasesMenu::showTicketsForCurrentUser()
{
    QString txtToSend = QString("{\"operation\":\"getUserTickets\", \"userName\":\"%1\"}").arg(bckEnd->getCurUserame());
    emit _dataToSend(txtToSend.toUtf8());
}

void PurchasesMenu::on_BuyButton_clicked()
{
    ui->BuyButton->setCheckable(0);
    QPixmap BuyIcon(":/recources/img/TrainIconFocus.png");
    ui->BuyButton->setIcon(BuyIcon);

    ui->ReserveButton->setCheckable(1);
    QPixmap ReservedIcon(":/recources/img/BookedTicketsIcon.png");
    ui->ReserveButton->setIcon(ReservedIcon);

    ui->LogOutButton->setCheckable(1);
    QPixmap LogOutIcon(":/recources/img/ExitIcon.png");
    ui->LogOutButton->setIcon(LogOutIcon);

    ui->stackedWidget->setCurrentWidget(BuyScreen);
}

void PurchasesMenu::on_ReserveButton_clicked()
{
    showTicketsForCurrentUser();

    ui->BuyButton->setCheckable(1);
    QPixmap BuyIcon(":/recources/img/TrainIcon.png");
    ui->BuyButton->setIcon(BuyIcon);

    ui->ReserveButton->setCheckable(0);
    QPixmap ReservedIcon(":/recources/img/BookedTicketsIconFocus.png");
    ui->ReserveButton->setIcon(ReservedIcon);

    ui->LogOutButton->setCheckable(1);
    QPixmap LogOutIcon(":/recources/img/ExitIcon.png");
    ui->LogOutButton->setIcon(LogOutIcon);

    ui->stackedWidget->setCurrentWidget(reserveScreen);
}

void PurchasesMenu::on_LogOutButton_clicked()
{

    ui->stackedWidget->setCurrentIndex(0);
    ui->BuyButton->setCheckable(1);
    QPixmap BuyIcon(":/recources/img/TrainIcon.png");
    ui->BuyButton->setIcon(BuyIcon);

    ui->ReserveButton->setCheckable(1);
    QPixmap ReservedIcon(":/recources/img/BookedTicketsIcon.png");
    ui->ReserveButton->setIcon(ReservedIcon);

    ui->LogOutButton->setCheckable(0);
    QPixmap LogOutIcon(":/recources/img/ExitIconFocus.png");
    ui->LogOutButton->setIcon(LogOutIcon);
}

void PurchasesMenu::on_exitButton_clicked()
{
    emit _closeApp();
}

void PurchasesMenu::on_logOutButton_clicked()
{

    emit _logOut();
}
