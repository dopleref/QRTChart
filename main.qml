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
        chartName1: "КРЛ1"
        chartName2: "КРЛ2"
        chartName3: "КРЛ3"
        chartName4: "КРЛ4"
        anchors.fill: parent
    }

    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            for (var i = 0; i < 4; i++) {
                var randValue = Math.random() * 200;
                qrtchart.append(i, randValue);
            }
        }
    }

    /*
    Triangle {
        anchors.centerIn: parent
        width: parent.width / 2
        height: parent.height / 2
    }
    */

}
