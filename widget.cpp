
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include "widget.h"
#include "ui_widget.h"
#include<QProgressBar>
#include "splashscreen.h"
#include<QThread>
#include"QRoundProgressBar.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
   /* //Show splash screen for 3 seconds
    SplashScreen splashScreen;
    splashScreen.show();
    QThread::sleep(14);//sleep for 3 seconds
    splashScreen.close();*/


    ui->setupUi(this);

   // heightprogressBar = new QProgressBar();

    arduino = new QSerialPort;
    serialBuffer = "";
    CrossSectionalArea = 657.47251054327;
    accelerationGravity = 980.665;//this is in cm/s2 though i would use in m/s2 by dividing it with 100
    ui->heightprogressBar->setRange(0, 15.60);
    ui->densityroundprogressBar->setRange(0,1.10);
    ui->densityroundprogressBar->setBarStyle(QRoundProgressBar::StyleDonut);
    ui->densityroundprogressBar->setFormat(QString("%v g/cm³"));

    //create a new round progress bar instance
   /* QRoundProgressBar*densityroundprogressBar = new QRoundProgressBar(this);
    densityroundprogressBar->setRange(0.0,100.0);
    densityroundprogressBar->resize(100,100);
    densityroundprogressBar->setBarStyle(QRoundProgressBar::StylePie);*/


    //pressureBuffer = "";
    //pressureScalingFactor = 0.070307;// Conversion factor from psi to pressure per square cm

    // ...



    /*
     *  Testing code, prints the description, vendor id, and product id of all ports.
     *  Used it to determine the values for the arduino uno.
     *
     *
    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }
    */


    /*
     *   Identify the port the arduino uno is on.
     */
    bool arduino_is_available = false;
    QString arduino_uno_port_name;
    //
    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            //  check if the product ID and the vendor ID match those of the arduino uno
            if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }

    /*
     *  Open and configure the arduino port if available
     */
    if(arduino_is_available){
        qDebug() << "Found the arduino port...\n";
        arduino->setPortName(arduino_uno_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        qDebug() << "Couldn't find the correct port for the arduino.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    }


}

Widget::~Widget()
{//Making sure not to leave the arduino open all the time;
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}
//create a function that is going to be called when the the application receives a signal from the arduino;

void Widget::readSerial() {
    QStringList bufferSplit = serialBuffer.split(",");
    if (bufferSplit.length() < 3) {
        // Read data from serial port
        QByteArray data = arduino->readAll();
        serialBuffer += QString::fromStdString(data.toStdString());

        // Convert serial buffer to floating point number
        bool conversionSuccessful = false;
        double heightvalueFloat = serialBuffer.toDouble(&conversionSuccessful);

        if (conversionSuccessful && heightvalueFloat >= 0 && heightvalueFloat <= 15.60) {
            // Convert floating point number to integer
            int heightvalue = static_cast<int>(heightvalueFloat * 100);
            //subtract height value from maximum value of progress bar to inverted value
            int invertedValue = ui->heightprogressBar->maximum() - heightvalue;




            // Update linear normal qtprogress bar
            ui->heightprogressBar->setRange(0, 1560);
            ui->heightprogressBar->setValue(invertedValue);





            //update the volume LCD number display
            double showVolume = CrossSectionalArea * invertedValue;//calculating the volume using the partial cone formular
            ui->volumelcdNumber->display(QString::number(showVolume,'f',2));


            //update The pressure LCD number display
            double pressure = 0.1*(15.60 - heightvalueFloat);//calculating the pressure using a scaling factor
            ui->lcdpressureNumber->display(QString::number(pressure, 'f', 2));//displaying the pressure with 2dp

            //calculating the density and displaying the density on the round progressbar
            double density = pressure/(accelerationGravity*invertedValue) * 1000 * 1000;

            //updating density on the round progress bar
            ui->densityroundprogressBar->setRange(0, 1.10);
            ui->densityroundprogressBar->setValue(density);



            // Print received value to output console
            qDebug() << "Received value: " << heightvalueFloat;
            qDebug() <<density;
            qDebug() <<showVolume;
        } else {
            // Print error message to output console
            qDebug() << "Error: Received value is not a valid floating point number or is out of range";
        }
    } else {
        // Convert serial buffer to floating point number
        bool conversionSuccessful = false;
        double heightvalueFloat = bufferSplit[1].toDouble(&conversionSuccessful);

        if (conversionSuccessful && heightvalueFloat >= 0 && heightvalueFloat <= 15.60) {
            // Convert floating point number to integer
            int heightvalue = static_cast<int>(heightvalueFloat * 100);
            // Subtract height value from maximum value of progress bar to invert the values
            int invertedValue = ui->heightprogressBar->maximum() - heightvalue;
            //calculating the volume and  displaying it
            double showVolume = CrossSectionalArea * invertedValue;//calculating the volume using the partial cone formular
            ui->volumelcdNumber->display(QString::number(showVolume,'f',2));

            //calculating the pressure
            double pressure = 0.1*(15.60 - heightvalueFloat);//calculating the pressure using a scaling factor


            //calculating the density
            double density = pressure/(accelerationGravity*invertedValue) * 1000 * 1000;


            // Updating both of the  progress bars (the linear progress bar and the round progress bars)
            ui->heightprogressBar->setRange(0, 1560);
            ui->heightprogressBar->setValue(invertedValue);
            ui->densityroundprogressBar->setRange(0,1.10);
            ui->densityroundprogressBar->setValue(density);

            // Print received value to output console
            qDebug() << "Received value: " << heightvalueFloat;
            qDebug() <<density;
            qDebug() <<showVolume;

        } else {
            // Print error message to output console
            qDebug() << "Error: Received value is not a valid floating point number or is out of range";
        }

        // Reset serial buffer
        serialBuffer = "";
    }
}


/*void Widget :: readSerial(){

   // qDebug()<<"Serial port works";


}*/

//now lets update the gui(progressbar)
//void Widget :: updateprogressBar(const QString sensor_reading){

//}
/*void Widget::updateProgress(QString sensor_reading)
{
    //  update the value displayed on the lcdNumber
    //ui->temp_lcdNumber->display(sensor_reading);

   // connect(&sensor_reading, SIGNAL(valueChanged(sensor_reading)), ui->heightprogressBar, SLOT(SetValue(sensor_reading));

}
*/


