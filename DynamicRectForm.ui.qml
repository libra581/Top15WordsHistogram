import QtQuick 2.4

Item {
    id: itemElement
    height: 20
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 20
    anchors.rightMargin: 20

    property alias rectBackground: rectBackground
    property alias rectFrontCount: rectFrontCount
    property alias textElement: textElement

    Text {
        id: textElement
        x: 8
        y: 3
        width: 112
        height: 14
        text: "Element1"
        elide: Text.ElideRight
        font.pixelSize: 12
    }

    Rectangle {
        id: rectBackground

        property alias rectFrontCount: rectFrontCount

        color: "#d2d2d2"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 120
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.rightMargin: 0

        Rectangle {
            id: rectFrontCount
            color: "#d06a5e"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 517
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 0
        }
    }
}
