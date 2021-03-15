import QtQuick 2.4
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 640
    height: 480

    property alias valueProgressBar: progressBar.value
    signal wellDone()

    ProgressBar {
        id: progressBar
        width: 200
        height: 36
        opacity: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        value: 0
        anchors.rightMargin: 25
        anchors.leftMargin: 25
        anchors.topMargin: 25
    }

    Text {
        id: textPrecent
        x: 597
        text: Math.round(progressBar.value * 100) + " %"
        anchors.right: parent.right
        anchors.top: parent.top
        font.pixelSize: 12
        anchors.topMargin: 25
        anchors.rightMargin: 20
    }

    Text {
        id: textLoadingFile
        text: qsTr("Загрузка файла")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        font.pixelSize: 12
        anchors.rightMargin: 529
        anchors.leftMargin: 25
        anchors.topMargin: 25
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}D{i:2}D{i:3}D{i:7}D{i:6}D{i:4}D{i:8}D{i:12}D{i:16}D{i:20}
}
##^##*/

