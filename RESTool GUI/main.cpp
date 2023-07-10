#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    mainWindow.setWindowIcon(QIcon(":/resources/icon1.ico"));

    return app.exec();
}