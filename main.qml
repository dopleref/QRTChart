import QtQuick 2.8
import QtQuick.Window 2.2
import Chart 1.0
import QRTChart 1.0

Window {
    id: root
    visible: true
    width: 1200
    height: 600
    title: qsTr("Custom Chart")

    QRTChart {
        id: qrtchart
        anchors.fill: parent
    }

}
