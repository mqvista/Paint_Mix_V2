import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page
    title: qsTr("Hiwave")


    Rectangle {
        id: rct1
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: - parent.width / 5
        width: 200
        height: 100
        color: "#66ccff"
        Text {
            id: text1
            text: qsTr("颜料配色模块")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 30
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                rct1.color = ""
            }
            onReleased: {
                rct1.color = "#66ccff"
                stView.push("PaintMix.qml")
            }
        }
    }

    Rectangle {
        id: rct2
        width: 200
        height: 100
        color: "#66ccff"
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: parent.width / 5
        Text {
            id: text2
            text: qsTr("其他功能模块")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 30
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                rct2.color = ""
            }
            onReleased: {
                rct2.color = "#66ccff"
                stView.push("PageSecond.qml")
            }
        }
    }
}
