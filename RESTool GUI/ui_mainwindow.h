/********************************************************************************
** Form generated from reading UI file 'mainwindowdgsOso.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWDGSOSO_H
#define MAINWINDOWDGSOSO_H

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
    QLabel* label;
    QPushButton* browseButton;
    QLineEdit* filenameLineEdit;
    QPushButton* unpackButton;
    QComboBox* modeComboBox;
    QCheckBox* checkBox;
    QLabel* label_2;
    QPushButton* makeResButton;
    QPlainTextEdit* debugTextEdit;
    QComboBox* packModeComboBox;

    void setupUi(QMainWindow* mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->resize(618, 380);
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        browseButton = new QPushButton(centralwidget);
        browseButton->setObjectName("browseButton");

        gridLayout->addWidget(browseButton, 1, 0, 1, 1);

        filenameLineEdit = new QLineEdit(centralwidget);
        filenameLineEdit->setObjectName("filenameLineEdit");
        filenameLineEdit->setEnabled(false);

        gridLayout->addWidget(filenameLineEdit, 1, 1, 1, 2);

        unpackButton = new QPushButton(centralwidget);
        unpackButton->setObjectName("unpackButton");

        gridLayout->addWidget(unpackButton, 2, 0, 1, 1);

        modeComboBox = new QComboBox(centralwidget);
        modeComboBox->setObjectName("modeComboBox");
        modeComboBox->setLayoutDirection(Qt::LeftToRight);
        modeComboBox->setEditable(false);

        gridLayout->addWidget(modeComboBox, 2, 1, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        checkBox->setLayoutDirection(Qt::RightToLeft);
        checkBox->setAutoFillBackground(false);

        gridLayout->addWidget(checkBox, 2, 2, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        makeResButton = new QPushButton(centralwidget);
        makeResButton->setObjectName("makeResButton");

        gridLayout->addWidget(makeResButton, 4, 0, 1, 1);

        debugTextEdit = new QPlainTextEdit(centralwidget);
        debugTextEdit->setObjectName("debugTextEdit");
        debugTextEdit->setReadOnly(true);

        gridLayout->addWidget(debugTextEdit, 5, 0, 1, 3);

        packModeComboBox = new QComboBox(centralwidget);
        packModeComboBox->setObjectName("packModeComboBox");

        gridLayout->addWidget(packModeComboBox, 4, 1, 1, 2);

        mainWindow->setCentralWidget(centralwidget);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow* mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "RESTool by Romalu86", nullptr));
        label->setText(QCoreApplication::translate("mainWindow", "Unpack options:", nullptr));
        browseButton->setText(QCoreApplication::translate("mainWindow", "Browse", nullptr));
        filenameLineEdit->setText(QCoreApplication::translate("mainWindow", "File not selected", nullptr));
        unpackButton->setText(QCoreApplication::translate("mainWindow", "Unpack", nullptr));
        checkBox->setText(QCoreApplication::translate("mainWindow", "Alternative unpacking mode:", nullptr));
        label_2->setText(QCoreApplication::translate("mainWindow", "Pack options:", nullptr));
        makeResButton->setText(QCoreApplication::translate("mainWindow", "MakeRes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow : public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWDGSOSO_H