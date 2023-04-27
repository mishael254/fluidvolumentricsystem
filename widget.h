
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSerialPort>
#include<QPainter>
#include"QRoundProgressBar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QRoundProgressBar*densityroundprogressBar;

private slots:
    void readSerial();
    //void updateHeight(QString);




private:
    Ui::Widget *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QByteArray serialData;
    QString serialBuffer;
    int heightvalue;
    QString pressureBuffer;
    float pressureScalingFactor;
    float CrossSectionalArea;
    double accelerationGravity;

};

#endif // WIDGET_H
