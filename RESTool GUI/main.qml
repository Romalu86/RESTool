/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.5
import QtQuick.Controls 6.5
import UntitledProject1

Rectangle {
    width: 400
    height: 150

    color: Constants.backgroundColor

    TextInput {
        id: filenameLabel
        x: 8
        y: 8
        width: 80
        height: 20
        text: qsTr("File:")
        font.pixelSize: 12
    }

    TextInput {
        id: filenameLineEdit
        x: 8
        y: 34
        width: 80
        height: 20
        text: "path to file"
        font.pixelSize: 12
    }

    Button {
        id: browseButton
        x: 8
        y: 60
        width: 184
        height: 32
        text: qsTr("Browse")
    }

    ComboBox {
        id: modeComboBox
        x: 208
        y: 60
        width: 184
        height: 32
    }

    TextInput {
        id: modeLabel
        x: 208
        y: 34
        width: 80
        height: 20
        text: "File mode:"
        font.pixelSize: 12
    }

    TextInput {
        id: alternativeModeLabel
        x: 286
        y: 104
        width: 80
        height: 20
        text: "Alternative Unpacking Mode:"
        font.pixelSize: 12
    }

    CheckBox {
        id: alternativeModeCheckBox
        x: 360
        y: 98
    }

    Button {
        id: unpackButton
        x: 8
        y: 98
        width: 184
        height: 32
        text: qsTr("Unpack")
    }
}

