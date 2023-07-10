/********************************************************************************
** Form generated from reading UI file 'mainwindowOYRslZ.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWOYRSLZ_H
#define MAINWINDOWOYRSLZ_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
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
    QFormLayout* formLayout;
    QPushButton* browseButton;
    QLineEdit* filenameLineEdit;
    QPushButton* unpackButton;
    QComboBox* modeComboBox;
    QPushButton* makeResButton;
    QComboBox* packModeComboBox;
    QPlainTextEdit* debugTextEdit;
    QLabel* label;
    QLabel* label_2;

    void setupUi(QMainWindow* mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->resize(630, 308);
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName("centralwidget");
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName("formLayout");
        browseButton = new QPushButton(centralwidget);
        browseButton->setObjectName("browseButton");

        formLayout->setWidget(1, QFormLayout::LabelRole, browseButton);

        filenameLineEdit = new QLineEdit(centralwidget);
        filenameLineEdit->setObjectName("filenameLineEdit");
        filenameLineEdit->setEnabled(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, filenameLineEdit);

        unpackButton = new QPushButton(centralwidget);
        unpackButton->setObjectName("unpackButton");

        formLayout->setWidget(2, QFormLayout::LabelRole, unpackButton);

        modeComboBox = new QComboBox(centralwidget);
        modeComboBox->setObjectName("modeComboBox");
        modeComboBox->setEditable(false);

        formLayout->setWidget(2, QFormLayout::FieldRole, modeComboBox);

        makeResButton = new QPushButton(centralwidget);
        makeResButton->setObjectName("makeResButton");

        formLayout->setWidget(4, QFormLayout::LabelRole, makeResButton);

        packModeComboBox = new QComboBox(centralwidget);
        packModeComboBox->setObjectName("packModeComboBox");

        formLayout->setWidget(4, QFormLayout::FieldRole, packModeComboBox);

        debugTextEdit = new QPlainTextEdit(centralwidget);
        debugTextEdit->setObjectName("debugTextEdit");
        debugTextEdit->setReadOnly(true);

        formLayout->setWidget(5, QFormLayout::SpanningRole, debugTextEdit);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        mainWindow->setCentralWidget(centralwidget);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow* mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "RESTool by Romalu86", nullptr));
        browseButton->setText(QCoreApplication::translate("mainWindow", "Browse", nullptr));
        filenameLineEdit->setText(QCoreApplication::translate("mainWindow", "File not selected", nullptr));
        unpackButton->setText(QCoreApplication::translate("mainWindow", "Unpack", nullptr));
        makeResButton->setText(QCoreApplication::translate("mainWindow", "MakeRes", nullptr));
        label->setText(QCoreApplication::translate("mainWindow", "Unpack options:", nullptr));
        label_2->setText(QCoreApplication::translate("mainWindow", "Pack options:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow : public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWOYRSLZ_H