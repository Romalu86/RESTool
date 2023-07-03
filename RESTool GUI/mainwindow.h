#ifndef MAINWINDOW_H
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


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void handleBrowseButtonClicked();
    void handleUnpackButtonClicked();
    void handleModeComboBoxChanged(const QString& mode);
    void handleMakeResButtonClicked();

private:
    static void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    static QPlainTextEdit* debugTextEdit;
    QLabel* filenameLabel;
    QLineEdit* filenameLineEdit;
    QPushButton* browseButton;
    QLabel* modeLabel;
    QComboBox* modeComboBox;
    QPushButton* unpackButton;
    bool alternativeModeEnabled;
};

#endif