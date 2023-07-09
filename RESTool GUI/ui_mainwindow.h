/********************************************************************************
** Form generated from reading UI file 'dialogdsRwGT.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DIALOGDSRWGT_H
#define DIALOGDSRWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget* centralwidget;
    QVBoxLayout* verticalLayout;
    QHBoxLayout* horizontalLayout;
    QPushButton* browseButton;
    QLineEdit* filenameLineEdit;
    QComboBox* modeComboBox;
    QPushButton* unpackButton;
    QFrame* line;
    QHBoxLayout* horizontalLayout2;
    QComboBox* packModeComboBox;
    QPushButton* makeResButton;
    QPlainTextEdit* debugTextEdit;

    void setupUi(QMainWindow* MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(755, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        browseButton = new QPushButton(centralwidget);
        browseButton->setObjectName("browseButton");

        horizontalLayout->addWidget(browseButton);

        filenameLineEdit = new QLineEdit(centralwidget);
        filenameLineEdit->setObjectName("filenameLineEdit");
        filenameLineEdit->setEnabled(false);
        filenameLineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(filenameLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        modeComboBox = new QComboBox(centralwidget);
        modeComboBox->setObjectName("modeComboBox");

        verticalLayout->addWidget(modeComboBox);

        unpackButton = new QPushButton(centralwidget);
        unpackButton->setObjectName("unpackButton");

        verticalLayout->addWidget(unpackButton);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout2 = new QHBoxLayout();
        horizontalLayout2->setObjectName("horizontalLayout2");
        packModeComboBox = new QComboBox(centralwidget);
        packModeComboBox->setObjectName("packModeComboBox");

        horizontalLayout2->addWidget(packModeComboBox);

        makeResButton = new QPushButton(centralwidget);
        makeResButton->setObjectName("makeResButton");

        horizontalLayout2->addWidget(makeResButton);


        verticalLayout->addLayout(horizontalLayout2);

        debugTextEdit = new QPlainTextEdit(centralwidget);
        debugTextEdit->setObjectName("debugTextEdit");
        debugTextEdit->setReadOnly(true);

        verticalLayout->addWidget(debugTextEdit);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }

    void retranslateUi(QMainWindow* MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "RESTool by Romalu86", nullptr));
        browseButton->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        filenameLineEdit->setText(QCoreApplication::translate("MainWindow", "File not selected", nullptr));
        unpackButton->setText(QCoreApplication::translate("MainWindow", "Unpack", nullptr));
        makeResButton->setText(QCoreApplication::translate("MainWindow", "MakeRes", nullptr));
    }

};

namespace Ui {
    class MainWindow : public Ui_MainWindow {};
}

QT_END_NAMESPACE

#endif
