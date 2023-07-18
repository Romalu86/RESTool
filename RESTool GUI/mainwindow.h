﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QFileDialog>

void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);


class QLineEdit;
class QPushButton;
class QComboBox;
class QPlainTextEdit;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void analyzeOBJIni();

private slots:
    void handleBrowseButtonClicked();
    void handleUnpackButtonClicked();
    void handleModeComboBoxChanged(const QString& mode);
    void handlePackModeComboBoxChanged(const QString& mode);
    void handleMakeResButtonClicked();
    void handleCheckBoxStateChanged(int state);
    void handleAnalyzeButtonClicked();

private:
    Ui::MainWindow* ui; // Указатель на экземпляр класса Ui::MainWindow
    static void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    static QPlainTextEdit* debugTextEdit;
    QPushButton* OpenFileAnalyzeButton;
    QLineEdit* FirstNVidlineEdit;
    QLineEdit* LastNVidlineEdit;
    QPushButton* AnalyzeButton;
    QPlainTextEdit* resultTextEdit;
    QCheckBox* checkBox;
    QPushButton* makeResButton;
    QComboBox* packModeComboBox;
    QLineEdit* filenameLineEdit;
    QPushButton* browseButton;
    QComboBox* modeComboBox;
    QPushButton* unpackButton;
    bool alternativeModeEnabled;
};

#endif