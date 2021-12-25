#include "buytickets.h"
#include "ui_buytickets.h"
#include <QGraphicsDropShadowEffect>


void BuyTickets::setShadowEff()
{
    QGraphicsDropShadowEffect* DepartEffect = new QGraphicsDropShadowEffect;
    DepartEffect->setBlurRadius(20);
    DepartEffect->setXOffset(0);
    DepartEffect->setYOffset(0);
    DepartEffect->setColor(Qt::black);
    ui->DepartureLineEdit->setGraphicsEffect(DepartEffect);

    QGraphicsDropShadowEffect* DestEffect = new QGraphicsDropShadowEffect;
    DestEffect->setBlurRadius(20);
    DestEffect->setXOffset(0);
    DestEffect->setYOffset(0);
    DestEffect->setColor(Qt::black);
    ui->DestinationLineEdit->setGraphicsEffect(DestEffect);

    QGraphicsDropShadowEffect* FromLabelEffect = new QGraphicsDropShadowEffect;
    FromLabelEffect->setBlurRadius(20);
    FromLabelEffect->setXOffset(0);
    FromLabelEffect->setYOffset(0);
    FromLabelEffect->setColor(Qt::black);
    ui->FromLabel->setGraphicsEffect(FromLabelEffect);

    QGraphicsDropShadowEffect* ToLabelEffect = new QGraphicsDropShadowEffect;
    ToLabelEffect->setBlurRadius(20);
    ToLabelEffect->setXOffset(0);
    ToLabelEffect->setYOffset(0);
    ToLabelEffect->setColor(Qt::black);
    ui->ToLabel->setGraphicsEffect(ToLabelEffect);

    QGraphicsDropShadowEffect* DepTimeLabEffect = new QGraphicsDropShadowEffect;
    DepTimeLabEffect->setBlurRadius(20);
    DepTimeLabEffect->setXOffset(0);
    DepTimeLabEffect->setYOffset(0);
    DepTimeLabEffect->setColor(Qt::black);
    ui->DepTimeLab->setGraphicsEffect(DepTimeLabEffect);

    QGraphicsDropShadowEffect* HourLabelEffect = new QGraphicsDropShadowEffect;
    HourLabelEffect->setBlurRadius(20);
    HourLabelEffect->setXOffset(0);
    HourLabelEffect->setYOffset(0);
    HourLabelEffect->setColor(Qt::black);
    ui->HourLabel->setGraphicsEffect(HourLabelEffect);

    QGraphicsDropShadowEffect* DateEditEffect = new QGraphicsDropShadowEffect;
    DateEditEffect->setBlurRadius(20);
    DateEditEffect->setXOffset(0);
    DateEditEffect->setYOffset(0);
    DateEditEffect->setColor(Qt::black);
    ui->DateEdit->setGraphicsEffect(DateEditEffect);

    QGraphicsDropShadowEffect* TimeEditEffect = new QGraphicsDropShadowEffect;
    TimeEditEffect->setBlurRadius(20);
    TimeEditEffect->setXOffset(0);
    TimeEditEffect->setYOffset(0);
    TimeEditEffect->setColor(Qt::black);
    ui->TimeEdit->setGraphicsEffect(TimeEditEffect);

    QGraphicsDropShadowEffect* SearchButtonEffect = new QGraphicsDropShadowEffect;
    SearchButtonEffect->setBlurRadius(20);
    SearchButtonEffect->setXOffset(0);
    SearchButtonEffect->setYOffset(0);
    SearchButtonEffect->setColor(Qt::black);
    ui->SearchButton->setGraphicsEffect(SearchButtonEffect);
}

void BuyTickets::setCompleterStyle(QAbstractItemView *popup)
{

    popup->setStyleSheet(" QListView {background-color:#37474F ;  "
                                             "                             "
                                             "     border-style: solid;    "
                                             "     border-width: 2px;      "
                                             "     border-color: #455A64;  "
                                             "     color:#ECEFF1;          "
                                             "     font-family: \" Calibri \"; "
                                             "     font-size: 13px;        }"
                                             "    QScrollBar:vertical {                                                              \
                     border: 2px solid #90A4AE;                                                     \
                     background: #263238;                                                           \
                     width: 15px;                                                                   \
                     margin: 22px 0 22px 0;                                                         \
                 }                                                                                  \
                 QScrollBar::handle:vertical {                                                      \
                     background: white;                                                             \
                     min-height: 20px;                                                              \
                 }                                                                                  \
                 QScrollBar::add-line:vertical {                                                    \
                     border: 2px solid grey;                                                        \
                     background: #32CC99;                                                           \
                     height: 20px;                                                                  \
                     subcontrol-position: bottom;                                                   \
                     subcontrol-origin: margin;                                                     \
                 }                                                                                  \
                                                                                                    \
                 QScrollBar::sub-line:vertical {                                                    \
                     border: 2px solid grey;                                                        \
                     background: #32CC99;                                                           \
                     height: 20px;                                                                  \
                     subcontrol-position: top;                                                      \
                     subcontrol-origin: margin;                                                     \
                 }                                                                                  \
                 QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {                   \
                     border: 2px solid grey;                                                        \
                     width: 3px;                                                                    \
                     height: 3px;                                                                   \
                     background: white;                                                             \
                 }                                                                                  \
                                                                                                    \
                 QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {                     \
                     background: none;\
                 }");
}

