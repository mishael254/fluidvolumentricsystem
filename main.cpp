#include "splashscreen.h"
#include "widget.h"
#include <QSplashScreen>
#include <QLabel>
#include <QVBoxLayout>
#include"QRoundProgressBar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //load the icon
    QIcon icon("C:/Users/Mishael/Pictures/Camera Roll/logo.jpg");
    a.setWindowIcon(icon);

    // Create and show the splash screen
    QPixmap logoPixmap("C:/Users/Mishael/Pictures/Camera Roll/logo2.jpeg");
    QSplashScreen splash(logoPixmap);
    QLabel projectLabel("AUTOMATED VOLUMENTRIC SYSTEM");
    QLabel versionLabel("Version 1.0");
    QVBoxLayout layout;
    layout.addWidget(&projectLabel);
    layout.addWidget(&versionLabel);
    splash.setLayout(&layout);
    //show the splash screen
    splash.setWindowIcon(icon);
    splash.show();

    // Add a delay to simulate loading time
    for (int i = 0; i < 700000000; i++);

    // Create and show the main window
    Widget w;
    w.setWindowTitle("AUTOMATED VOLUMENTRIC SYSTEM");
    w.setWindowIcon(icon);
    w.show();

    // Hide and delete the splash screen
    splash.finish(&w);

    return a.exec();
}
