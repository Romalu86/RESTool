#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include "mainwindow.h"

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QFile file("log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
        switch (type)
        {
        case QtDebugMsg:
            stream << "" << msg << "\n";
            break;
        case QtWarningMsg:
            stream << "" << msg << "\n";
            break;
        case QtCriticalMsg:
            stream << "" << msg << "\n";
            break;
        case QtFatalMsg:
            stream << "" << msg << "\n";
            break;
        }
        file.close();
    }
}

int main(int argc, char* argv[])
{
    qInstallMessageHandler(messageHandler);
    qSetMessagePattern("%{message}");

    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}