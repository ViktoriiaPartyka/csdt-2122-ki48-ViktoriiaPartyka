#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>

// set shadows in Log and Reg menus
void MainWindow::setShadowEff()
{
    QGraphicsDropShadowEffect* LogEffect = new QGraphicsDropShadowEffect;
    LogEffect->setBlurRadius(20);
    LogEffect->setXOffset(0);
    LogEffect->setYOffset(0);
    LogEffect->setColor(Qt::black);
    ui->LoginLineEdit->setGraphicsEffect(LogEffect);

    QGraphicsDropShadowEffect* PassEffect = new QGraphicsDropShadowEffect;
    PassEffect->setBlurRadius(20);
    PassEffect->setXOffset(0);
    PassEffect->setYOffset(0);
    PassEffect->setColor(Qt::black);
    ui->PassLineEdit->setGraphicsEffect(PassEffect);

    QGraphicsDropShadowEffect* LogButtonEffect = new QGraphicsDropShadowEffect;
    LogButtonEffect->setBlurRadius(20);
    LogButtonEffect->setXOffset(0);
    LogButtonEffect->setYOffset(0);
    LogButtonEffect->setColor(Qt::black);
    ui->LogButton->setGraphicsEffect(LogButtonEffect);

    QGraphicsDropShadowEffect* REgButtonEffect = new QGraphicsDropShadowEffect;
    REgButtonEffect->setBlurRadius(20);
    REgButtonEffect->setXOffset(0);
    REgButtonEffect->setYOffset(0);
    REgButtonEffect->setColor(Qt::black);
    ui->RegButton->setGraphicsEffect(REgButtonEffect);

    QGraphicsDropShadowEffect* ExitEffect = new QGraphicsDropShadowEffect;
    ExitEffect->setBlurRadius(20);
    ExitEffect->setXOffset(0);
    ExitEffect->setYOffset(0);
    ExitEffect->setColor(Qt::black);
    ui->ExitButton->setGraphicsEffect(ExitEffect);

    QGraphicsDropShadowEffect* RegLofEffect = new QGraphicsDropShadowEffect;
    RegLofEffect->setBlurRadius(20);
    RegLofEffect->setXOffset(0);
    RegLofEffect->setYOffset(0);
    RegLofEffect->setColor(Qt::black);
    ui->RegLogLineEdit->setGraphicsEffect(RegLofEffect);

    QGraphicsDropShadowEffect* RegPassEffect = new QGraphicsDropShadowEffect;
    RegPassEffect->setBlurRadius(20);
    RegPassEffect->setXOffset(0);
    RegPassEffect->setYOffset(0);
    RegPassEffect->setColor(Qt::black);
    ui->RegPassLineEdit->setGraphicsEffect(RegPassEffect);

    QGraphicsDropShadowEffect* RegPConfEffect = new QGraphicsDropShadowEffect;
    RegPConfEffect->setBlurRadius(20);
    RegPConfEffect->setXOffset(0);
    RegPConfEffect->setYOffset(0);
    RegPConfEffect->setColor(Qt::black);
    ui->RegConfLineEdit->setGraphicsEffect(RegPConfEffect);

    QGraphicsDropShadowEffect* RegRegfEffect = new QGraphicsDropShadowEffect;
    RegRegfEffect->setBlurRadius(20);
    RegRegfEffect->setXOffset(0);
    RegRegfEffect->setYOffset(0);
    RegRegfEffect->setColor(Qt::black);
    ui->RegRegButton->setGraphicsEffect(RegRegfEffect);

    QGraphicsDropShadowEffect* RegBackfEffect = new QGraphicsDropShadowEffect;
    RegBackfEffect->setBlurRadius(20);
    RegBackfEffect->setXOffset(0);
    RegBackfEffect->setYOffset(0);
    RegBackfEffect->setColor(Qt::black);
    ui->RegGoBackButton->setGraphicsEffect(RegBackfEffect);

    retryLoadingYesBtn->setStyleSheet("QPushButton"
                                                                        "{"
                                                                        "background-color: rgba(242, 150, 47, 220);"
                                                                        "border:none;"
                                                                        "border-radius:10px;"
                                                                        "color:#1b2327;"
                                                                        "font-family:  \"Calibri Bold\";"
                                                                        "font-size: 17px;"
                                                                        "}"
                                                                        "QPushButton:hover:!pressed{"
                                                                        "background-color: #455A64;"
                                                                        "color:#EEEEEE;"
                                                                        "}"
                                                                        "QPushButton:hover:pressed{"
                                                                        "   background-color: #37474F;"
                                                                        "color:#DDDDDD;"
                                                                        "}");

    retryLoadingNoBtn->setStyleSheet("QPushButton"
                                                                     "{"
                                                                     "background-color: rgba(242, 150, 47, 220);"
                                                                     "border:none;"
                                                                     "border-radius:10px;"
                                                                     "color:#1b2327;"
                                                                     "font-family:  \"Calibri Bold\";"
                                                                     "font-size: 17px;"
                                                                     "}"
                                                                     "QPushButton:hover:!pressed{"
                                                                     "background-color: #455A64;"
                                                                     "color:#EEEEEE;"
                                                                     "}"
                                                                     "QPushButton:hover:pressed{"
                                                                     "   background-color: #37474F;"
                                                                     "color:#DDDDDD;"
                                                                     "}");

    retConnLabel->setStyleSheet("QLabel{"
                                                            "background:none ;"
                                                            "color:#EEEEEE;"
                                                            "font: \"Calibri\";"
                                                            "font-size: 14px;"
                                                            "}");
}

void MainWindow::resizeLoadindScreen()
{
    short wW = this->width();
    short wH = this->height();
    short hM = 10;
    short totalH = retConnLabel->height() + retryLoadingYesBtn->height() + 2 * hM;
    short totalW = retryLoadingYesBtn->width() + retryLoadingNoBtn->width() + 20;
    loadingBckGround->resize(wW, wH);
    loadingBckGround->move(0, 0);

    loadingGif->move(wW / 2 - loadingGif->width() / 2 + 25, wH / 2 - loadingGif->height() / 2);

    retConnLabel->move(wW / 2 - retConnLabel->width() / 2, wH / 2 - totalH / 2);
    retryLoadingYesBtn->move(wW / 2 - totalW / 2, wH / 2 - totalH / 2 + retConnLabel->height() + hM);
    retryLoadingNoBtn->move(wW / 2 - totalW / 2 + retryLoadingYesBtn->width() + 20, wH / 2 - totalH / 2 + retConnLabel->height() + hM);
}

// resizing Log menuacording ro window size
void MainWindow::resizeLogMenu()
{
    const short hMarg = 6;
    const short betweenMarg = 50;

    const short wW = this->size().width();
    const short wH = this->size().height();

    const short LeH = 22 + wH / 50;
    const short LeW = 250 + wW / 15;

    const short bH = 17 + wH / 75;
    const short bW = 52 + wW / 25;

    const short CbH = ui->RemMeCheckBox->size().height();
    const short CbW = ui->RemMeCheckBox->size().width();

    short totalHeight = 4 * hMarg + betweenMarg + 2 * LeH + 3 * bH + CbH;

    ui->LoginLineEdit->resize(LeW, LeH);
    ui->PassLineEdit->resize(LeW, LeH);

    ui->LoginLineEdit->move(wW / 2 - LeW / 2, wH / 2 - totalHeight / 2);
    ui->PassLineEdit->move(wW / 2 - LeW / 2, wH / 2 - totalHeight / 2 + LeH + hMarg);

    ui->RemMeCheckBox->move(wW / 2 - LeW / 2, wH / 2 - totalHeight / 2 + LeH + hMarg + LeH + hMarg);

    ui->LogButton->resize(bW, bH);
    ui->RegButton->resize(bW, bH);
    ui->ExitButton->resize(bW, bH);

    ui->LogButton->move(wW / 2 - bW / 2, wH / 2 - totalHeight / 2 + LeH + hMarg + LeH + betweenMarg);
    ui->RegButton->move(wW / 2 - bW / 2, wH / 2 - totalHeight / 2 + LeH + hMarg + LeH + betweenMarg + bH + hMarg);
    ui->ExitButton->move(wW / 2 - bW / 2, wH / 2 - totalHeight / 2 + LeH + hMarg + LeH + betweenMarg + bH + hMarg + bH + hMarg);

    QString bordRadButton = "QPushButton { border-radius: " + QString::number(bH / 2) + "px; }";
    QString bordRadLe = "QLineEdit { border-radius: " + QString::number(LeH / 4) + "px; }";
    ui->LogButton->setStyleSheet(bordRadButton);
    ui->RegButton->setStyleSheet(bordRadButton);
    ui->ExitButton->setStyleSheet(bordRadButton);
    ui->LoginLineEdit->setStyleSheet(bordRadLe);
    ui->PassLineEdit->setStyleSheet(bordRadLe);
}

// resizing Reg menuacording ro window size
void MainWindow::resizeRegMenu()
{
    const short hMarg = 6;
    const short betweenMarg = 30;

    const short wW = this->size().width();
    const short wH = this->size().height();

    const short LeH = 22 + wH / 50;
    const short LeW = 250 + wW / 15;

    const short bH = 17 + wH / 75;
    const short bW = 52 + wW / 25;

    short totalHeight = 2 * hMarg + betweenMarg + 3 * LeH + bH;

    ui->RegLogLineEdit->resize(LeW, LeH);
    ui->RegPassLineEdit->resize(LeW, LeH);
    ui->RegConfLineEdit->resize(LeW, LeH);

    ui->RegLogLineEdit->move(wW / 2 - LeW / 2, wH / 2 - totalHeight / 2);
    ui->RegPassLineEdit->move(wW / 2 - LeW / 2, wH / 2 - totalHeight / 2 + LeH + hMarg);
    ui->RegConfLineEdit->move(wW / 2 - LeW / 2, wH / 2 - totalHeight / 2 + LeH + hMarg + LeH + hMarg);

    ui->RegRegButton->resize(bW, bH);

    ui->RegRegButton->move(wW / 2 - bW / 2, wH / 2 - totalHeight / 2 + LeH + hMarg + LeH + hMarg + LeH + betweenMarg);

    QString bordRadButton = "QPushButton { border-radius: " + QString::number(bH / 2) + "px; }";
    QString bordRadLe = "QLineEdit { border-radius: " + QString::number(LeH / 4) + "px; }";
    ui->RegLogLineEdit->setStyleSheet(bordRadLe);
    ui->RegPassLineEdit->setStyleSheet(bordRadLe);
    ui->RegConfLineEdit->setStyleSheet(bordRadLe);
    ui->RegRegButton->setStyleSheet(bordRadButton);
}
