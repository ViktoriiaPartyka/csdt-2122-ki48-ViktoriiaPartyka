#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// secondary libreries
#include <QEvent>
#include <QToolTip>
#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <purchasesmenu.h>
// for communication with server
#include <backend.h>
// for multi threading
#include <QThread>
// for showing gifs
#include <QMovie>
// for loading screen
#include <QLabel>
// for format of strings checking
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_RegRegButton_clicked();
    void on_ExitButton_clicked();
    void on_RegButton_clicked();
    void on_RegGoBackButton_clicked();
    void on_LogButton_clicked();
    void retryLoadingYesBtn_clicked();
    void on_LoginLineEdit_textChanged(const QString& arg1);
    void on_PassLineEdit_textEdited(const QString& arg1);
    void resizeEvent(QResizeEvent*);	// redefinition of QResize event
    void loadScrnShow();	// show loading screen
    void loadScrnHide();	// hide loading screen
    void logSuccess();
    void regSuccess();	// go to lof menu if registration is successful
    void errSlot(QString Info);
    void logOutSlot();

private:
    Ui::MainWindow* ui;
    QThread* secThread;
    BackEnd* bckEnd;
    QLabel* loadingGif;
    QLabel* retConnLabel;
    QLabel* loadingBckGround;
    QMovie* movie;
    QPushButton* retryLoadingYesBtn;
    QPushButton* retryLoadingNoBtn;
    PurchasesMenu* OvScreen;	 // main menu screen
    void resizeLogMenu();	 // resizing elements in Log menu when window size changes
    void resizeRegMenu();	 // resizing elements in Reg menu when window size changes
    void setShadowEff();	// set shadows in Log and Reg menus
    void resizeLoadindScreen();	 // resizing loading screen

signals:
    void _dataToSend(QByteArray dataToSend);	// emit this signal when you need send data to server
    void _tryToReconn();	// tells back end to try to reconnect to server
};
#endif	// MAINWINDOW_H
