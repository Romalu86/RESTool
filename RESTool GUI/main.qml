/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.5
import QtQuick.Controls 6.5
import UntitledProject2

Rectangle {
    width: 600
    height: 370

    color: Constants.backgroundColor

    TextField {
        id: filenameLineEdit
        x: 8
        y: 36
        width: 286
        height: 40
        text: "File not selected"
        horizontalAlignment: Text.AlignHCenter
        readOnly: true
        enabled: false
        placeholderText: qsTr("Text Field")
    }

    Button {
        id: button
        x: 8
        y: 82
        width: 286
        height: 40
        text: qsTr("Browse")
    }

    ComboBox {
        id: modeComboBox
        x: 8
        y: 128
        width: 286
        height: 40
    }

    Button {
        id: button1
        x: 8
        y: 174
        width: 286
        height: 40
        text: qsTr("Unpack")
    }

    Label {
        id: label
        x: 8
        y: -3
        text: qsTr("Unpack options:")
        font.pointSize: 19
    }

    Label {
        id: label1
        x: 8
        y: 224
        text: qsTr("Compile options:")
        font.pointSize: 19
    }

    ComboBox {
        id: packModeComboBox
        x: 8
        y: 263
        width: 286
        height: 40
    }

    Button {
        id: button2
        x: 8
        y: 309
        width: 286
        height: 40
        text: qsTr("MakeRes")
    }

    TextEdit {
        id: debugTextEdit
        x: 308
        y: 36
        width: 284
        height: 313
        text: qsTr("Text Edit")
        font.pixelSize: 12
        enabled: false
        readOnly: true
    }
}