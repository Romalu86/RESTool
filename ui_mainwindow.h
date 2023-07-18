/********************************************************************************
** Form generated from reading UI file 'mainwindowhgtkNJ.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWHGTKNJ_H
#define MAINWINDOWHGTKNJ_H

#include <QtCore/QVariant>
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

class Ui_mainWindow
{
public:
    QWidget* centralwidget;
    QGridLayout* gridLayout;
    QComboBox* packModeComboBox;
    QComboBox* modeComboBox;
    QLabel* label_2;
    QLabel* label_4;
    QLineEdit* LastNVidlineEdit;
    QLabel* label_5;
    QPushButton* unpackButton;
    QLabel* label_3;
    QPushButton* browseButton;
    QLineEdit* filenameLineEdit;
    QPlainTextEdit* debugTextEdit;
    QPushButton* makeResButton;
    QCheckBox* checkBox;
    QLabel* label;
    QLineEdit* FirstNVidlineEdit;
    QPushButton* AnalyzeButton;

    void setupUi(QMainWindow* mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->resize(494, 574);
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        packModeComboBox = new QComboBox(centralwidget);
        packModeComboBox->setObjectName("packModeComboBox");

        gridLayout->addWidget(packModeComboBox, 4, 1, 1, 2);

        modeComboBox = new QComboBox(centralwidget);
        modeComboBox->setObjectName("modeComboBox");
        modeComboBox->setLayoutDirection(Qt::LeftToRight);
        modeComboBox->setEditable(false);

        gridLayout->addWidget(modeComboBox, 2, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 7, 1, 1, 1);

        LastNVidlineEdit = new QLineEdit(centralwidget);
        LastNVidlineEdit->setObjectName("LastNVidlineEdit");

        gridLayout->addWidget(LastNVidlineEdit, 8, 2, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 7, 2, 1, 1);

        unpackButton = new QPushButton(centralwidget);
        unpackButton->setObjectName("unpackButton");

        gridLayout->addWidget(unpackButton, 2, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        browseButton = new QPushButton(centralwidget);
        browseButton->setObjectName("browseButton");

        gridLayout->addWidget(browseButton, 1, 0, 1, 1);

        filenameLineEdit = new QLineEdit(centralwidget);
        filenameLineEdit->setObjectName("filenameLineEdit");
        filenameLineEdit->setEnabled(true);
        filenameLineEdit->setReadOnly(true);

        gridLayout->addWidget(filenameLineEdit, 1, 1, 1, 2);

        debugTextEdit = new QPlainTextEdit(centralwidget);
        debugTextEdit->setObjectName("debugTextEdit");
        debugTextEdit->setReadOnly(true);

        gridLayout->addWidget(debugTextEdit, 9, 0, 1, 3);

        makeResButton = new QPushButton(centralwidget);
        makeResButton->setObjectName("makeResButton");

        gridLayout->addWidget(makeResButton, 4, 0, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        checkBox->setLayoutDirection(Qt::RightToLeft);
        checkBox->setAutoFillBackground(false);
        checkBox->setCheckable(true);

        gridLayout->addWidget(checkBox, 2, 2, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        FirstNVidlineEdit = new QLineEdit(centralwidget);
        FirstNVidlineEdit->setObjectName("FirstNVidlineEdit");
        FirstNVidlineEdit->setReadOnly(false);

        gridLayout->addWidget(FirstNVidlineEdit, 8, 1, 1, 1);

        AnalyzeButton = new QPushButton(centralwidget);
        AnalyzeButton->setObjectName("AnalyzeButton");

        gridLayout->addWidget(AnalyzeButton, 7, 0, 2, 1);

        mainWindow->setCentralWidget(centralwidget);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow* mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "RESTool by Romalu86", nullptr));
        label_2->setText(QCoreApplication::translate("mainWindow", "Pack options:", nullptr));
        label_4->setText(QCoreApplication::translate("mainWindow", "First NVid:", nullptr));
        LastNVidlineEdit->setText(QCoreApplication::translate("mainWindow", "4095", nullptr));
        label_5->setText(QCoreApplication::translate("mainWindow", "Last NVid:", nullptr));
        unpackButton->setText(QCoreApplication::translate("mainWindow", "Unpack", nullptr));
        label_3->setText(QCoreApplication::translate("mainWindow", "NVid Counter options:", nullptr));
        browseButton->setText(QCoreApplication::translate("mainWindow", "Browse", nullptr));
        filenameLineEdit->setText(QCoreApplication::translate("mainWindow", "File not selected", nullptr));
        makeResButton->setText(QCoreApplication::translate("mainWindow", "MakeRes", nullptr));
#if QT_CONFIG(tooltip)
        checkBox->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        checkBox->setText(QCoreApplication::translate("mainWindow", "Alternative unpacking mode:", nullptr));
        label->setText(QCoreApplication::translate("mainWindow", "Unpack options:", nullptr));
        FirstNVidlineEdit->setText(QCoreApplication::translate("mainWindow", "0", nullptr));
        AnalyzeButton->setText(QCoreApplication::translate("mainWindow", "Analyze OBJ.ini", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow : public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWHGTKNJ_H
