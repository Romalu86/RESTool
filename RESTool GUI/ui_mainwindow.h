/********************************************************************************
** Form generated from reading UI file 'mainwindowHlJLMm.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWHLJLMM_H
#define MAINWINDOWHLJLMM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *browseButton;
    QPushButton *unpackButton;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *modeComboBox;
    QCheckBox *checkBox;
    QLabel *label_2;
    QPushButton *makeResButton;
    QLabel *label_3;
    QPushButton *AnalyzeButton;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *FirstNVidlineEdit;
    QLineEdit *LastNVidlineEdit;
    QPlainTextEdit *debugTextEdit;
    QComboBox *packModeComboBox;
    QLineEdit *filenameLineEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(577, 574);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icon1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        browseButton = new QPushButton(centralwidget);
        browseButton->setObjectName("browseButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/file_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        browseButton->setIcon(icon1);

        gridLayout->addWidget(browseButton, 1, 0, 1, 1);

        unpackButton = new QPushButton(centralwidget);
        unpackButton->setObjectName("unpackButton");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/unpack.png"), QSize(), QIcon::Normal, QIcon::Off);
        unpackButton->setIcon(icon2);

        gridLayout->addWidget(unpackButton, 2, 0, 2, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 2, 1, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setTextFormat(Qt::AutoText);
        label_7->setScaledContents(true);
        label_7->setWordWrap(false);
        label_7->setMargin(1);

        gridLayout->addWidget(label_7, 2, 2, 1, 1, Qt::AlignHCenter);

        modeComboBox = new QComboBox(centralwidget);
        modeComboBox->setObjectName("modeComboBox");
        modeComboBox->setLayoutDirection(Qt::LeftToRight);
        modeComboBox->setEditable(false);

        gridLayout->addWidget(modeComboBox, 3, 1, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        checkBox->setLayoutDirection(Qt::LeftToRight);
        checkBox->setAutoFillBackground(false);
        checkBox->setCheckable(true);

        gridLayout->addWidget(checkBox, 3, 2, 1, 1, Qt::AlignHCenter);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        makeResButton = new QPushButton(centralwidget);
        makeResButton->setObjectName("makeResButton");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/pack.png"), QSize(), QIcon::Normal, QIcon::Off);
        makeResButton->setIcon(icon3);

        gridLayout->addWidget(makeResButton, 5, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        AnalyzeButton = new QPushButton(centralwidget);
        AnalyzeButton->setObjectName("AnalyzeButton");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/file_analyze.png"), QSize(), QIcon::Normal, QIcon::Off);
        AnalyzeButton->setIcon(icon4);

        gridLayout->addWidget(AnalyzeButton, 7, 0, 2, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 7, 1, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 7, 2, 1, 1);

        FirstNVidlineEdit = new QLineEdit(centralwidget);
        FirstNVidlineEdit->setObjectName("FirstNVidlineEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(FirstNVidlineEdit->sizePolicy().hasHeightForWidth());
        FirstNVidlineEdit->setSizePolicy(sizePolicy1);
        FirstNVidlineEdit->setReadOnly(false);

        gridLayout->addWidget(FirstNVidlineEdit, 8, 1, 1, 1);

        LastNVidlineEdit = new QLineEdit(centralwidget);
        LastNVidlineEdit->setObjectName("LastNVidlineEdit");
        LastNVidlineEdit->setMinimumSize(QSize(179, 0));

        gridLayout->addWidget(LastNVidlineEdit, 8, 2, 1, 1);

        debugTextEdit = new QPlainTextEdit(centralwidget);
        debugTextEdit->setObjectName("debugTextEdit");
        debugTextEdit->setReadOnly(true);

        gridLayout->addWidget(debugTextEdit, 9, 0, 1, 3);

        packModeComboBox = new QComboBox(centralwidget);
        packModeComboBox->setObjectName("packModeComboBox");

        gridLayout->addWidget(packModeComboBox, 5, 1, 1, 2);

        filenameLineEdit = new QLineEdit(centralwidget);
        filenameLineEdit->setObjectName("filenameLineEdit");
        filenameLineEdit->setEnabled(true);
        filenameLineEdit->setReadOnly(true);

        gridLayout->addWidget(filenameLineEdit, 1, 1, 1, 2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "RESTool by Romalu86", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Unpack options:", nullptr));
#if QT_CONFIG(tooltip)
        browseButton->setToolTip(QCoreApplication::translate("MainWindow", "Open the resource file.", nullptr));
#endif // QT_CONFIG(tooltip)
        browseButton->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
#if QT_CONFIG(tooltip)
        unpackButton->setToolTip(QCoreApplication::translate("MainWindow", "Initiate the process of unpacking the resource file.", nullptr));
#endif // QT_CONFIG(tooltip)
        unpackButton->setText(QCoreApplication::translate("MainWindow", "Unpack", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Game engine:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ff0000;\">Troubles with unpack? Use it!</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        modeComboBox->setToolTip(QCoreApplication::translate("MainWindow", "Mode selection for unpacking. Incorrect selection may result in data reading errors.\n"
" You can review the list of supported games below.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        modeComboBox->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        modeComboBox->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(tooltip)
        checkBox->setToolTip(QCoreApplication::translate("MainWindow", "An alternative unpacking mode is needed in case of incorrect data reading between sections of the file.\n"
" When modifying the source code, empty bytes are added, and this option allows reading or ignoring them.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox->setText(QCoreApplication::translate("MainWindow", "Alternative unpacking mode", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Pack options:", nullptr));
#if QT_CONFIG(tooltip)
        makeResButton->setToolTip(QCoreApplication::translate("MainWindow", "Initiate the process of packing the source data into a resource file.", nullptr));
#endif // QT_CONFIG(tooltip)
        makeResButton->setText(QCoreApplication::translate("MainWindow", "MakeRes", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "NVid Counter options:", nullptr));
#if QT_CONFIG(tooltip)
        AnalyzeButton->setToolTip(QCoreApplication::translate("MainWindow", "Open the file with objects for analysis (OBJ.ini or Objects.ini). The field below\n"
" will display the result with numbering of free and used NVid records.", nullptr));
#endif // QT_CONFIG(tooltip)
        AnalyzeButton->setText(QCoreApplication::translate("MainWindow", "Analyze OBJ.ini", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "First NVid:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Last NVid:", nullptr));
#if QT_CONFIG(tooltip)
        FirstNVidlineEdit->setToolTip(QCoreApplication::translate("MainWindow", "The number of the first entry in the OBJ.ini (Objects.ini) file is usually \"0\" or \"000\"\n"
" and it is not recommended to change this value.", nullptr));
#endif // QT_CONFIG(tooltip)
        FirstNVidlineEdit->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(tooltip)
        LastNVidlineEdit->setToolTip(QCoreApplication::translate("MainWindow", "The number of the last entry in the OBJ.ini (Objects.ini) file depends on the maximum\n"
" limit set in the games. Currently, the maximum limits are 2047 and 4095.", nullptr));
#endif // QT_CONFIG(tooltip)
        LastNVidlineEdit->setText(QCoreApplication::translate("MainWindow", "4095", nullptr));
#if QT_CONFIG(tooltip)
        packModeComboBox->setToolTip(QCoreApplication::translate("MainWindow", "Mode selection for packing the source data into a resource file.\n"
" You can review the list of supported games below.", nullptr));
#endif // QT_CONFIG(tooltip)
        filenameLineEdit->setText(QCoreApplication::translate("MainWindow", "File not selected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWHLJLMM_H
