#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

// secondary libraries
#include <QDialog>
#include <QLabel>
// for showing gifs
#include <QMovie>

namespace Ui
{
class LoadingScreen;
}

class LoadingScreen : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingScreen(QWidget* parent = nullptr);
    ~LoadingScreen();
    QMovie* movie;

private:
    Ui::LoadingScreen* ui;
};

#endif	// LOADINGSCREEN_H
