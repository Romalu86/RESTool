#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTimer>
#include <QString>
#include <QMap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void handleBrowseButtonClicked();
    void handleUnpackButtonClicked();
    void handleAlternativeModeCheckBoxClicked(bool checked);

private:
    QLabel* filenameLabel;
    QLineEdit* filenameLineEdit;
    QPushButton* browseButton;
    QLabel* modeLabel;
    QComboBox* modeComboBox;
    QLabel* alternativeModeLabel;
    QCheckBox* alternativeModeCheckBox;
    QPushButton* unpackButton;
    bool alternativeModeEnabled;
};

#endif // MAINWINDOW_H