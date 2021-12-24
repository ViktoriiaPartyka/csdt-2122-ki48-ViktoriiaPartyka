#include "reserveticketsmenu.h"
#include "ui_reserveticketsmenu.h"

reserveTicketsMenu::reserveTicketsMenu(BackEnd* bckEnd, QWidget* parent) : QWidget(parent), ui(new Ui::reserveTicketsMenu)
{
    ui->setupUi(this);
    this->bckEnd = bckEnd;

    connect(bckEnd, SIGNAL(_userTickets(QVariantList, QVariantList, QVariantList)), this,
                    SLOT(showUserTickets(QVariantList, QVariantList, QVariantList)));

    connect(this, SIGNAL(_dataToSend(QByteArray)), bckEnd, SLOT(sendData(QByteArray)));
    connect(bckEnd, SIGNAL(_reservedTicketBought()), this, SLOT(reservedTicketBought()));
    connect(bckEnd, SIGNAL(_returnTicket()), this, SLOT(returnTicket()));

    ui->unActiveTicketsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->unActiveTicketsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->unActiveTicketsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->boughtTicketsModel = nullptr;
    this->reservedTicketsModel = nullptr;
    this->unActiveTicketsModel = nullptr;

    ui->boughtTicketsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->boughtTicketsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->boughtTicketsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->boughtTicketsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->reservedTicketsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reservedTicketsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->reservedTicketsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->reservedTicketsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->unActiveTicketsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->unActiveTicketsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->unActiveTicketsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->unActiveTicketsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tabWidget->setCurrentIndex(0);

    ui->buyButton->hide();
    ui->returnButton->hide();
    ui->ownerFname->hide();
    ui->ownerLname->hide();
}

reserveTicketsMenu::~reserveTicketsMenu()
{
    delete ui;
}

void reserveTicketsMenu::showBoughtTickets(QVariantList boughtTicketsList)
{
    delete boughtTicketsModel;

    if (boughtTicketsList.length() == 0)
    {
        boughtTicketsModel = new QStandardItemModel(1, 1, this);
        QModelIndex modelIndex;

        modelIndex = boughtTicketsModel->index(0, 0);
        boughtTicketsModel->setData(modelIndex, "You dont have any bought tickets that are active", Qt::DisplayRole);

        ui->boughtTicketsTable->setModel(boughtTicketsModel);

        boughtTicketsModel->setHeaderData(0, Qt::Horizontal, "Information");
        ui->boughtTicketsTable->setSelectionMode(QAbstractItemView::NoSelection);
        return;
    }

    ui->boughtTicketsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    QModelIndex modelIndex;

    QStringList jsonFields = { "trainId",			"trainDate",	"dep",				"dest",					"wagonNumber",
                                                         "placeNumber", "ownerFname", "ownerLname", "purchaseDate", "purchaseTime" };

    boughtTicketsModel = new QStandardItemModel(boughtTicketsList.length(), jsonFields.length(), this);

    int row = 0;
    int col = 0;
    for (auto& _ticket : boughtTicketsList)
    {
        col = 0;
        QJsonObject ticket = _ticket.toJsonObject();

        for (QString& field : jsonFields)
        {
            modelIndex = boughtTicketsModel->index(row, col);
            boughtTicketsModel->setData(modelIndex, ticket.value(field).toString(), Qt::DisplayRole);
            ++col;
        }

        ui->boughtTicketsTable->setModel(boughtTicketsModel);

        ++row;
    }

    QStringList headerNames = { "Train id",			"Departure date", "Departure",			 "Destination",		"Wagon number",
                                                            "Place number", "Owner name",			"Owner last name", "Purchase date", "Purchase time" };

    for (int i = 0; i < headerNames.length(); ++i)
    {
        boughtTicketsModel->setHeaderData(i, Qt::Horizontal, headerNames[i]);
    }
}

void reserveTicketsMenu::showReservedTickets(QVariantList reservedTicketsList)
{
    delete reservedTicketsModel;

    if (reservedTicketsList.length() == 0)
    {
        reservedTicketsModel = new QStandardItemModel(1, 1, this);
        QModelIndex modelIndex;

        modelIndex = reservedTicketsModel->index(0, 0);
        reservedTicketsModel->setData(modelIndex, "You dont have any reserved tickets that are active", Qt::DisplayRole);

        ui->reservedTicketsTable->setModel(reservedTicketsModel);

        reservedTicketsModel->setHeaderData(0, Qt::Horizontal, "Information");

        disconnect(ui->reservedTicketsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(reservedTicketTableClicked(QModelIndex)));

        ui->reservedTicketsTable->setSelectionMode(QAbstractItemView::NoSelection);
        return;
    }

    connect(ui->reservedTicketsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(reservedTicketTableClicked(QModelIndex)));
    ui->reservedTicketsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList jsonFields = { "trainId",			"trainDate",	"dep",				"dest",					"wagonNumber",
                                                         "placeNumber", "ownerFname", "ownerLname", "purchaseDate", "purchaseTime" };

    reservedTicketsModel = new QStandardItemModel(reservedTicketsList.length(), jsonFields.length(), this);

    QModelIndex modelIndex;

    int row = 0;
    int col = 0;
    for (auto& _ticket : reservedTicketsList)
    {
        col = 0;
        QJsonObject ticket = _ticket.toJsonObject();

        for (QString& field : jsonFields)
        {
            modelIndex = reservedTicketsModel->index(row, col);
            reservedTicketsModel->setData(modelIndex, ticket.value(field).toString(), Qt::DisplayRole);
            ++col;
        }

        ui->reservedTicketsTable->setModel(reservedTicketsModel);

        ++row;
    }

    QStringList headerNames = { "Train id",			"Departure date", "Departure",			 "Destination",			 "Wagon number",
                                                            "Place number", "Owner name",			"Owner last name", "Reservation date", "Reservation time" };

    for (int i = 0; i < headerNames.length(); ++i)
    {
        reservedTicketsModel->setHeaderData(i, Qt::Horizontal, headerNames[i]);
    }
}

void reserveTicketsMenu::showUnActiveTickets(QVariantList unActiveTicketsList)
{
    delete unActiveTicketsModel;

    if (unActiveTicketsList.length() == 0)
    {
        unActiveTicketsModel = new QStandardItemModel(1, 1, this);
        QModelIndex modelIndex;

        modelIndex = unActiveTicketsModel->index(0, 0);
        unActiveTicketsModel->setData(modelIndex, "You dont have any unactive tickets", Qt::DisplayRole);

        ui->unActiveTicketsTable->setModel(unActiveTicketsModel);

        unActiveTicketsModel->setHeaderData(0, Qt::Horizontal, "Information");
        ui->unActiveTicketsTable->setSelectionMode(QAbstractItemView::NoSelection);
        return;
    }
    ui->unActiveTicketsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList jsonFields = { "trainId",		 "trainDate",	 "dep",					 "dest",				 "wagonNumber", "placeNumber",
                                                         "ownerFname", "ownerLname", "purchaseDate", "purchaseTime", "buyOrRes" };

    unActiveTicketsModel = new QStandardItemModel(unActiveTicketsList.length(), jsonFields.length(), this);

    QModelIndex modelIndex;

    int row = 0;
    int col = 0;
    for (auto& _ticket : unActiveTicketsList)
    {
        col = 0;
        QJsonObject ticket = _ticket.toJsonObject();

        for (QString& field : jsonFields)
        {
            if (field == "buyOrRes")
            {
                if (ticket.value(field).toString() == "0")
                {
                    modelIndex = unActiveTicketsModel->index(row, col);
                    unActiveTicketsModel->setData(modelIndex, "Bought", Qt::DisplayRole);
                }
                else
                {
                    modelIndex = unActiveTicketsModel->index(row, col);
                    unActiveTicketsModel->setData(modelIndex, "Reserved", Qt::DisplayRole);
                }
            }
            else
            {
                modelIndex = unActiveTicketsModel->index(row, col);
                unActiveTicketsModel->setData(modelIndex, ticket.value(field).toString(), Qt::DisplayRole);
            }
            ++col;
        }

        ui->unActiveTicketsTable->setModel(unActiveTicketsModel);

        ++row;
    }

    QStringList headerNames = { "Train id",		"Departure date",	 "Departure",				 "Destination",			 "Wagon number", "Place number",
                                                            "Owner name", "Owner last name", "Reservation date", "Reservation time", "Status" };

    for (int i = 0; i < headerNames.length(); ++i)
    {
        unActiveTicketsModel->setHeaderData(i, Qt::Horizontal, headerNames[i]);
    }
}

void reserveTicketsMenu::showUserTickets(QVariantList unActiveTickets, QVariantList boughtTickets, QVariantList reservedTickets)
{
    showBoughtTickets(boughtTickets);
    showReservedTickets(reservedTickets);
    showUnActiveTickets(unActiveTickets);
}

void reserveTicketsMenu::reservedTicketTableClicked(const QModelIndex& index)
{
    reservedTicketIndex = index;

    ui->buyButton->show();
    ui->returnButton->show();
    ui->ownerFname->show();
    ui->ownerLname->show();

    reservedTicketIndex = reservedTicketsModel->index(reservedTicketIndex.row(), 6);
    ui->ownerFname->setText(reservedTicketsModel->data(reservedTicketIndex).toString());

    reservedTicketIndex = reservedTicketsModel->index(reservedTicketIndex.row(), 7);
    ui->ownerLname->setText(reservedTicketsModel->data(reservedTicketIndex).toString());
}

void reserveTicketsMenu::on_tabWidget_currentChanged(int index)
{
    ui->boughtTicketsTable->clearSelection();
    ui->buyButton->hide();
    ui->returnButton->hide();
    ui->ownerFname->hide();
    ui->ownerLname->hide();
}

void reserveTicketsMenu::on_buyButton_clicked()
{
    ui->reservedTicketsTable->selectRow(reservedTicketIndex.row());

    QString fName = ui->ownerFname->text();
    QString lName = ui->ownerLname->text();

    QRegularExpression rgx("[\\p{Cyrillic}[a-zA-z]{1,50}");

    if (fName.length() == 0)
    {
        bckEnd->showErrorMsg(ui->ownerFname, "First name can't be empty");
        return;
    }
    if (lName.length() == 0)
    {
        bckEnd->showErrorMsg(ui->ownerLname, "Last name can't be empty");
        return;
    }
    if (rgx.match(fName).capturedLength() != fName.length())
    {
        bckEnd->showErrorMsg(ui->ownerFname, "first name can only contain latin and cyrylic characters");
        return;
    }
    if (rgx.match(lName).capturedLength() != lName.length())
    {
        bckEnd->showErrorMsg(ui->ownerFname, "last name can only contain latin and cyrylic characters");
        return;
    }

    int row = reservedTicketIndex.row();

    QString ticketInfo = "{\"operation\":\"buyReservedTicket\", \"trainId\":\"%1\", \"trainDate\":\"%2\", \"dep\":\"%3\", \"dest\":\"%4\", "
                                             "\"wagonNumber\":\"%5\", "
                                             "\"placeNumber\":\"%6\", \"fName\":\"%7\", \"lName\":\"%8\"}";
    for (int column = 0; column < 8; ++column)
    {
        reservedTicketIndex = reservedTicketsModel->index(row, column);
        QString modelData = reservedTicketsModel->data(reservedTicketIndex).toString();

        ticketInfo.replace("%" + QString::number(column + 1), modelData);
    }

    emit _dataToSend(ticketInfo.toUtf8());
}

void reserveTicketsMenu::on_returnButton_clicked()
{
    ui->reservedTicketsTable->selectRow(reservedTicketIndex.row());

    int row = reservedTicketIndex.row();

    QString ticketInfo = "{\"operation\":\"returnTicket\", \"trainId\":\"%1\", \"trainDate\":\"%2\", \"dep\":\"%3\", \"dest\":\"%4\", "
                                             "\"wagonNumber\":\"%5\", "
                                             "\"placeNumber\":\"%6\"}";
    for (int column = 0; column < 6; ++column)
    {
        reservedTicketIndex = reservedTicketsModel->index(row, column);
        QString modelData = reservedTicketsModel->data(reservedTicketIndex).toString();

        ticketInfo.replace("%" + QString::number(column + 1), modelData);
    }

    emit _dataToSend(ticketInfo.toUtf8());
}

void reserveTicketsMenu::reservedTicketBought()
{
    QString txtToSend = QString("{\"operation\":\"getUserTickets\", \"userName\":\"%1\"}").arg(bckEnd->getCurUserame());
    emit _dataToSend(txtToSend.toUtf8());

    bckEnd->showErrorMsg(ui->ownerLname, "Reserved ticket bought successfully");

    ui->buyButton->hide();
    ui->returnButton->hide();
    ui->ownerFname->hide();
    ui->ownerLname->hide();
}

void reserveTicketsMenu::returnTicket()
{
    QString txtToSend = QString("{\"operation\":\"getUserTickets\", \"userName\":\"%1\"}").arg(bckEnd->getCurUserame());
    emit _dataToSend(txtToSend.toUtf8());

    bckEnd->showErrorMsg(ui->ownerLname, "Ticket returned successfully");

    ui->buyButton->hide();
    ui->returnButton->hide();
    ui->ownerFname->hide();
    ui->ownerLname->hide();
}
