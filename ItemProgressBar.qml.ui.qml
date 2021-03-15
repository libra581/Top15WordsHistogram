import QtQuick 2.4
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 500
    height: 40

    ProgressBar {
        id: progressBarControl
        anchors.fill: parent
        font.pointSize: 8
        value: 0.0
    }
}
