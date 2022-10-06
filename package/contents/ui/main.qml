import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.5 as QQC2

import com.suzakuwcx.todonextplugin 1.0 as TNP

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 3.0 as PlasmaComponents3
import org.kde.plasma.plasmoid 2.0

Item {
    id: root

    TNP.TodoNext {
        id: todonext
    }

    width: PlasmaCore.Units.gridUnit * 15
    height: PlasmaCore.Units.gridUnit * 15

    Layout.minimumWidth: PlasmaCore.Units.gridUnit * 15
    Layout.minimumHeight: PlasmaCore.Units.gridUnit * 15

    Plasmoid.switchWidth: PlasmaCore.Units.gridUnit * 11
    Plasmoid.switchHeight: PlasmaCore.Units.gridUnit * 11

    PlasmaComponents3.Label {
        id: taskLabel

        font.pixelSize: 24
        font.bold : true
        text: i18n("Next Task: ")
        
        anchors.left: parent.left
        anchors.top: parent.top
    }
    PlasmaComponents3.ToolButton {
        id: inputButton

        visible: true
        icon.name: "cursor-cross"
        text: i18n("Add")
    
        anchors.right: parent.right
        anchors.verticalCenter: taskLabel.verticalCenter
        
        // onClicked: {
        //     
        // }
    }
    Column {
        id: column

        anchors.right: parent.right        
        anchors.bottom: parent.bottom

        PlasmaComponents3.ToolButton {
            visible: true
            icon.name: "gnumeric-format-valign-bottom"
            text: i18n("Push")
            
            // onClicked: {
            //     
            // }
        }
        PlasmaComponents3.ToolButton {
            visible: true
            icon.name: "dialog-ok"
            text: i18n("Finish")
            
            // onClicked: {
            //     
            // }
        }
    }
    PlasmaComponents3.ScrollView {

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: taskLabel.bottom
        anchors.right: column.left

        PlasmaComponents3.TextArea {
            id: task

            font.pixelSize: 18
            text: "Placeholder"
            readOnly: true
            wrapMode: TextEdit.WrapAnywhere            
            
            anchors.fill: parent

            // To cover TextArea deafult frame appearance
            background: Item {
                anchors.fill: parent
            }
        }            
    }
}
