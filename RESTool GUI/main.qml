import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    width: 370
    height: 300

    Column {
        spacing: 10

        TextField {
            id: filenameLineEdit
            placeholderText: "File not selected"
            enabled: false
        }

        Button {
            text: "Browse"
            onClicked: handleBrowseButtonClicked()
        }

        ComboBox {
            id: modeComboBox
            model: ["as1_engine", "theseus_pc", "as1world", "zs1", "zs1_mobile", "as2_original", "as2_addons", "zs2_engine", "as2legend_engine", "oe_engine", "crazylunch", "chackstemple", "locoland"]
            onCurrentTextChanged: handleModeComboBoxChanged(currentText)
        }

        Button {
            text: "Unpack"
            onClicked: handleUnpackButtonClicked()
        }

        Rectangle {
            height: 1
            width: parent.width
            color: "black"
        }

        ComboBox {
            id: packModeComboBox
            model: ["AS/ZS Engine", "Objects Extended Engine", "Locoland Engine"]
            onCurrentTextChanged: handlePackModeComboBoxChanged(currentText)
        }

        Button {
            text: "MakeRes"
            onClicked: handleMakeResButtonClicked()
        }

        TextArea {
            id: debugTextEdit
            readOnly: true
        }
    }

    function handleBrowseButtonClicked() {
        // Добавьте соответствующую логику обработки события в вашем коде
    }

    function handleUnpackButtonClicked() {
        // Добавьте соответствующую логику обработки события в вашем коде
    }

    function handleModeComboBoxChanged(text) {
        // Добавьте соответствующую логику обработки события в вашем коде
    }

    function handlePackModeComboBoxChanged(text) {
        // Добавьте соответствующую логику обработки события в вашем коде
    }

    function handleMakeResButtonClicked() {
        // Добавьте соответствующую логику обработки события в вашем коде
    }
}