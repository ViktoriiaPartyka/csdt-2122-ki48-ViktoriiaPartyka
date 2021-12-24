#include "loadingscreen.h"
#include "ui_loadingscreen.h"

LoadingScreen::LoadingScreen(QWidget* parent) : QDialog(parent), ui(new Ui::LoadingScreen)
{
    // this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::CustomizeWindowHint);
    ui->setupUi(this);
    movie = new QMovie(":/recources/img/loadingGif.gif");
    ui->mLabel->setMovie(movie);
    ui->mLabel->show();
    movie->start();
}

LoadingScreen::~LoadingScreen()
{
    delete ui;
}
