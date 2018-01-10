import QtQuick 2.8
import QtQuick.Window 2.2
import Chart 1.0

Window {
    visible: true
    width: 1200
    height: 600
    title: qsTr("Custom Chart")

    CustomChart {
        id: chart
        anchors.fill: parent
    }

    Component.onCompleted: {
        chart.init()
    }
}
