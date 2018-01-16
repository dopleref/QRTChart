import QtQuick 2.8
import QtQuick.Window 2.2
import QRTChart 1.0
import Shapes 1.0

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

    /*
    Triangle {
        anchors.centerIn: parent
        width: parent.width / 2
        height: parent.height / 2
    }
    */

}
