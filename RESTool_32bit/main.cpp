#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QTimer>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Создание дополнительного окна с изображением
    QMainWindow splashWindow;
    QLabel splashLabel(&splashWindow);
    splashLabel.setPixmap(QPixmap(":/resources/banner.png"));
    splashWindow.setCentralWidget(&splashLabel);
    splashWindow.setWindowFlags(Qt::SplashScreen);

    // Отображение дополнительного окна
    splashWindow.show();

    // Задержка в течение 1 секунды
    QTimer::singleShot(1000, &splashWindow, &QMainWindow::hide);

    // Создание главного окна
    MainWindow mainWindow;

    // Отображение главного окна после скрытия дополнительного окна
    QTimer::singleShot(1000, &mainWindow, &MainWindow::show);

    return app.exec();
}