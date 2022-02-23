import QtQuick 2.12

Rectangle {
    id: root
    property alias internalText: valueText
    color: "lightgreen"
    border.color: "black"
    border.width: 1
    radius: 5
    width: 100
    height: 100

    Text {
        id: valueText
        text: "1"
        anchors.centerIn:  root.Center

        font.bold: true
        font.pointSize: root.height * 0.33
    }
}
