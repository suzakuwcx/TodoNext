import QtQuick 2.0
import QtQuick.Layouts 1.0

import org.kde.plasma.components 3.0 as PlasmaComponents3

Item {
    id: root

    property var title
    property var minimumWidth
    property var minimumHeight
    property Component mainItem
    
    Layout.minimumWidth: minimumWidth
    Layout.minimumHeight: minimumHeight
    PlasmaComponents3.Label {
        id: fatherLabel

        font.pixelSize: 24
        font.bold : true
        text: i18n(title)
        
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
    }
    // White line
    Rectangle {
        id: splitLine

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: fatherLabel.bottom

        height: 1
    }
    // space
    Item {
        id: space

        anchors.top: splitLine.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        
        height: 3
    }
    Loader {
        id: loader

        anchors.top: space.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        sourceComponent: mainItem
    }
}