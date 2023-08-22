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
    void handleVIDmodeComboBoxChanged(const QString& mode);
    void handleMakeResButtonClicked();
    void handleCheckBoxStateChanged(int state);
    void handleAnalyzeButtonClicked();
    void handleOpenVidButtonClicked();
    void handleConvertVidButtonClicked();
    void analyzeOBJIni(const QString& filePath);
    //
    void changeThemeToFusion();
    void changeThemeToWindows();
    void openVKLink();
    void openOELink();

private:
    Ui::MainWindow* ui;
    static void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    static QPlainTextEdit* debugTextEdit;
    // QMenuBar
    QMenuBar* appMenuBar;
    QMenuBar* linksMenuBar;
    QAction* openFileAction;
    QAction* analyzeFileAction;
    QAction* fusionThemeAction;
    QAction* windowsThemeAction;
    QAction* VidConvertAction;
    QAction* VKLink;
    QAction* OEProjectLink;
    //
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
    //Vid Viewer
    QComboBox* VIDmodeComboBox;
    QPushButton* OpenVIDButton;
    QPushButton* ConvertVIDButton;
    //
    bool alternativeModeEnabled;
};

#endif