#include "mainwindow.h"
#include <UiHelperMainWindow.cpp>
#include "ui_mainwindow.h"

// constructor
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create blue background for loading screen
    loadingBckGround = new QLabel(this);
    loadingBckGround->setStyleSheet("QLabel{background-color:rgb(38,50,56);}");

    // create view for gif
    loadingGif = new QLabel(this);
    loadingGif->resize(200, 124);
    movie = new QMovie(":/recources/img/loadingGif.gif");
    movie->setScaledSize(QSize(loadingGif->width(), loadingGif->height()));
    loadingGif->setMovie(movie);
    movie->setSpeed(110);

    // create buttons for loading screen
    retryLoadingYesBtn = new QPushButton(this);
    retryLoadingNoBtn = new QPushButton(this);
    retryLoadingYesBtn->setText("Retry");
    retryLoadingNoBtn->setText("Quit app");

    // create lable to show text on loading screen
    retConnLabel = new QLabel(this);
    retConnLabel->setText("Could not connect to server. Do you want to rty again?");
    retConnLabel->resize(345, 17);

    // setting Log menu as starting screen (0 is index of login menu in stackedwidget)
    ui->stackedWidget->setCurrentIndex(0);

    // calling func to make shadows in login and reg menus
    setShadowEff();

    // creating new backend
    bckEnd = new BackEnd();

    // crerate new thread this makes possible showing animations while connecting
    secThread = new QThread(this);

    // quit second thred when app closes
    connect(this, SIGNAL(destroyed()), secThread, SLOT(quit()));

    // create socket and connect to server when new threa started
    connect(secThread, SIGNAL(started()), bckEnd, SLOT(createSocket()));

    // to be able to send data to bckEnd object
    connect(this, SIGNAL(_dataToSend(QByteArray)), bckEnd, SLOT(sendData(QByteArray)));

    // when back end can not connect to server show loading screen
    connect(bckEnd, SIGNAL(_reconnFailed()), this, SLOT(loadScrnShow()));

    // close loading screen when connection restored
    connect(bckEnd, SIGNAL(_reconnSuccess()), this, SLOT(loadScrnHide()));

    // when loginization is successful
    connect(bckEnd, SIGNAL(_logSuccess()), this, SLOT(logSuccess()));

    // when registration is successful
    connect(bckEnd, SIGNAL(_regSuccess()), this, SLOT(regSuccess()));

    // when error in log or reg process
    connect(bckEnd, SIGNAL(_errSignalMW(QString)), this, SLOT(errSlot(QString)));

    // when user dont want to try connecting again
    connect(retryLoadingNoBtn, SIGNAL(clicked()), this, SLOT(on_ExitButton_clicked()));

    // when user dont want to try connecting again
    connect(retryLoadingYesBtn, SIGNAL(clicked()), bckEnd, SLOT(tryToReccon()));

    // show gif while trying to conect
    connect(retryLoadingYesBtn, SIGNAL(clicked()), this, SLOT(retryLoadingYesBtn_clicked()));

    // start new thread
    bckEnd->moveToThread(secThread);
    secThread->start();

    resizeLoadindScreen();

    // check if any user pressed remember me
    QFile rMeFile(".remMe");
    if (rMeFile.open(QIODevice::ReadOnly))
    {
        {
            ui->LoginLineEdit->setText(rMeFile.readLine().replace("\n", ""));
            ui->PassLineEdit->setText(rMeFile.readLine().replace("\n", ""));
            rMeFile.close();
            if (ui->LoginLineEdit->text() != "")
            {
                ui->RemMeCheckBox->setChecked(1);
                ui->LogButton->animateClick(0);
            }
        }
    }
}

// destructor
MainWindow::~MainWindow()
{
    secThread->quit();
    secThread->wait();
    delete bckEnd;
    delete ui;
}

void MainWindow::on_LoginLineEdit_textChanged(const QString& arg1)
{
    ui->LoginLineEdit->setStyleSheet("border-color: #455A64;");
}

void MainWindow::on_PassLineEdit_textEdited(const QString& arg1)
{
    ui->PassLineEdit->setStyleSheet("border-color: #455A64;");
}

void MainWindow::on_RegButton_clicked()
{
    resizeRegMenu();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_LogButton_clicked()
{
    QString logTxt = ui->LoginLineEdit->text();
    QString passTxt = ui->PassLineEdit->text();
    QRegularExpression logPattern("[a-zA-Z0-9@.]{5,}");
    QRegularExpression passPattern("[a-zA-Z0-9]{6,}");

    if (logPattern.match(logTxt).capturedLength() >= 5 && logPattern.match(logTxt).capturedLength() == logTxt.length())

    {
        if (passPattern.match(passTxt).capturedLength() >= 6 && passPattern.match(passTxt).capturedLength() == passTxt.length())

        {
            QString txtToSend = QString("{\"operation\":\"login\", \"log\":\"%1\", \"pass\":\"%2\"}").arg(logTxt).arg(passTxt);

            emit _dataToSend(txtToSend.toUtf8());
        }

        else
        {
            bckEnd->showErrorMsg(ui->PassLineEdit, "Password can only contain latin letters and numbers and must be longer than 6 characters");
        }
    }
    // if log format is incorrect
    else
    {
        // check pass format
        if (passPattern.match(passTxt).capturedLength() < 6 || passPattern.match(passTxt).capturedLength() != passTxt.length())
        // if password format is incorrect
        {
            bckEnd->showErrorMsg(ui->LoginLineEdit, "<p>Login can only contain latin letters, numbers and characters . and @ and must be longer than 5 "
                                                                                            "characters</p>"
                                                                                            "<p>Password can only contain latin letters and numbers and must be longer than 6 characters</p>");
        }
        else
        {
            bckEnd->showErrorMsg(ui->LoginLineEdit, "Login can only contain latin letters, numbers and characters . and @ and must be longer than 5 "
                                                                                            "characters");
        }
    }
}

void MainWindow::retryLoadingYesBtn_clicked()
{
    retryLoadingYesBtn->hide();
    retryLoadingNoBtn->hide();
    retConnLabel->hide();
    movie->start();
    loadingGif->show();
}

void MainWindow::on_ExitButton_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setObjectName("msgBox");
    msgBox.setStyleSheet("#msgBox{ background-color:#1e282d;}"
                                             "QLabel{background:none;color:#e4e4e4;font-family: \"Calibri\";font-size: 14px;border:none;}"
                                             "QPushButton{width:60px;background-color: rgba(242, 150, 47, 220);border:none;border-radius:10px;color:#1b2327;font-family:  "
                                             "\"Calibri "
                                             "Bold\";font-size: 17px;}"
                                             "QPushButton:hover:!pressed{background-color: #455A64;color:#EEEEEE;}"
                                             "QPushButton:hover:pressed{background-color: #37474F;color:#DDDDDD;}");

    msgBox.setWindowTitle("Exit confirmation");
    msgBox.setInformativeText("<p>Do you want to exit the app?<p>");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int userAnswer = msgBox.exec();

    if (userAnswer == QMessageBox::Yes)
    {
        this->close();
    }
}

void MainWindow::on_RegGoBackButton_clicked()
{
    resizeLogMenu();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_RegRegButton_clicked()
{
    QString logTxt = ui->RegLogLineEdit->text();
    QString passTxt = ui->RegPassLineEdit->text();
    QString confTxt = ui->RegConfLineEdit->text();
    QRegularExpression logFormat("[a-zA-Z0-9@.]{5,}");
    QRegularExpression passFormat("[A-Za-z0-9]{6,}");

    if (logFormat.match(logTxt).capturedLength() >= 5 && logFormat.match(logTxt).capturedLength() == logTxt.length())
    // if login fits log format
    {
        if (passFormat.match(passTxt).capturedLength() >= 6 && passFormat.match(passTxt).capturedLength() == passTxt.length())
        // if pass match pass format
        {
            if (passTxt == confTxt)
            // if pass==conf
            {
                // read data from line edits and convert it to JSON format
                QString txtToSend = QString("{\"operation\":\"register\", \"log\":\"%1\", \"pass\":\"%2\"}").arg(logTxt).arg(passTxt);

                // send log and pass to server
                emit _dataToSend(txtToSend.toUtf8());
            }
            else
            {
                bckEnd->showErrorMsg(ui->RegConfLineEdit, "Password and confirm field must match");
            }
        }
        else
        {
            bckEnd->showErrorMsg(ui->RegPassLineEdit, "Password can only contain latin letters and numbers and must be longer than 6 characters");
        }
    }
    // if login doesnt match needed format
    else
    {
        if (passFormat.match(passTxt).capturedLength() < 6 || passFormat.match(passTxt).capturedLength() != passTxt.length())
        // if pass doesnt match needed format
        {
            bckEnd->showErrorMsg(ui->RegPassLineEdit, "<p>Login can only contain latin letters, numbers and characters . and @ and must be longer than 5 "
                                                                                                "characters</p>"
                                                                                                "<p>Password can only contain latin letters and numbers and must be longer than 6 characters</p>");
        }
        else
        {
            bckEnd->showErrorMsg(ui->RegLogLineEdit, "Login can only contain latin letters, numbers and characters . and @ and must be longer than 5 "
                                                                                             "characters");
        }
    }
}

// for handeling MainWindow resize event
void MainWindow::resizeEvent(QResizeEvent* event)
{
    if (loadingBckGround->isVisible())
    {
        resizeLoadindScreen();
    }
    if (ui->stackedWidget->currentIndex() == 0)
    {
        resizeLogMenu();
    }
    else if (ui->stackedWidget->currentIndex() == 1)
    {
        resizeRegMenu();
    }
    QWidget::resizeEvent(event);
}

void MainWindow::loadScrnShow()
{
    retryLoadingYesBtn->show();
    retryLoadingNoBtn->show();
    retConnLabel->show();
    movie->stop();
    loadingGif->hide();
    if (!loadingBckGround->isVisible())
    {
        resizeLoadindScreen();
        loadingGif->show();
        loadingBckGround->show();
    }
}

void MainWindow::loadScrnHide()
{
    retryLoadingYesBtn->hide();
    retryLoadingNoBtn->hide();
    retConnLabel->hide();
    movie->stop();
    loadingBckGround->hide();
    loadingGif->hide();
}

void MainWindow::logSuccess()
{
    QDir dir(QCoreApplication::applicationDirPath() + ".remMe");
    QFile rMeFile(".remMe");

    bckEnd->setCurUsername(ui->LoginLineEdit->text());

    // if remember me is checked
    // write log and pass to remME file
    if (rMeFile.open(QIODevice::WriteOnly))
    {
        if (ui->RemMeCheckBox->isChecked())
        {
            {
                QString fileInputTex = ui->LoginLineEdit->text() + "\n" + ui->PassLineEdit->text();
                rMeFile.write(fileInputTex.toUtf8());
                rMeFile.waitForBytesWritten(100);
                rMeFile.close();
            }
        }
        else
        {
            rMeFile.close();
        }
    }

    // adding main menu ui to stacked widget
    OvScreen = new PurchasesMenu(bckEnd);
    ui->stackedWidget->addWidget(OvScreen);

    connect(OvScreen, SIGNAL(_closeApp()), this, SLOT(on_ExitButton_clicked()));

    connect(OvScreen, SIGNAL(_logOut()), this, SLOT(logOutSlot()));

    // go to main menu
    ui->stackedWidget->setCurrentWidget(OvScreen);

    // send lrequest to get cities list
    emit _dataToSend("{\"operation\":\"getCities\"}");
}

void MainWindow::regSuccess()
{
    ui->stackedWidget->setCurrentIndex(0);
    bckEnd->showErrorMsg(ui->LoginLineEdit, "Registration is successful, now you can login.");
}

void MainWindow::errSlot(QString Info)
{
    if (Info == "Login doesn't exist")
    {
        bckEnd->showErrorMsg(ui->LoginLineEdit, "Login doesn't exist");
        ui->LoginLineEdit->setStyleSheet("border-color:#990329;");
    }
    else if (Info == "Invalid password")
    {
        bckEnd->showErrorMsg(ui->PassLineEdit, "Invalid password");
        ui->PassLineEdit->setStyleSheet("border-color:#990329;");
    }
    else if (Info == "User already exist")
    {
        bckEnd->showErrorMsg(ui->RegLogLineEdit, "User already exist");
    }
    else
    {
        QMessageBox::critical(this, "Fatal error", Info);
    }
}

void MainWindow::logOutSlot()
{
    QMessageBox msgBox(this);
    msgBox.setObjectName("msgBox");
    msgBox.setStyleSheet("#msgBox{ background-color:#1e282d;}"
                                             "QLabel{background:none;color:#e4e4e4;font-family: \"Calibri\";font-size: 14px;border:none;}"
                                             "QPushButton{width:60px;background-color: rgba(242, 150, 47, 220);border:none;border-radius:10px;color:#1b2327;font-family:  "
                                             "\"Calibri "
                                             "Bold\";font-size: 17px;}"
                                             "QPushButton:hover:!pressed{background-color: #455A64;color:#EEEEEE;}"
                                             "QPushButton:hover:pressed{background-color: #37474F;color:#DDDDDD;}");

    msgBox.setWindowTitle("Exit confirmation");
    msgBox.setInformativeText("<p>Do you want to exit the app?<p>");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int userAnswer = msgBox.exec();

    if (userAnswer == QMessageBox::No)
    {
        return;
    }
    else
    {
        ui->stackedWidget->removeWidget(OvScreen);

        disconnect(OvScreen, SIGNAL(_closeApp()), this, SLOT(on_ExitButton_clicked()));

        disconnect(OvScreen, SIGNAL(_logOut()), this, SLOT(logOutSlot()));

        QFile rMeFile(".remMe");

        rMeFile.open(QIODevice::WriteOnly);
        rMeFile.close();

        ui->LoginLineEdit->clear();
        ui->PassLineEdit->clear();

        resizeLogMenu();
        ui->stackedWidget->setCurrentIndex(0);

        delete OvScreen;
    }
}
