import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: item1
    Rectangle {
        id: mainRectangle
        width: parent.width / 1.2
        height: parent.height / 1.2
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.verticalCenter:  parent.verticalCenter
        radius: 5
        border.width: 5
        border.color: "Silver"

        Button {
            id: button
            width: 200
            height: 80
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.height * -0.3
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: parent.width * -0.2
            text: qsTr("移液到外部")
            font.pointSize: 28
            onClicked: {
                taskModule.test();
            }
            enabled: !taskModule.busy
        }

        Text {
            id: outsideWeightName
            text: qsTr("移出重量: ")
            font.pointSize: 28
            anchors.verticalCenter: button.verticalCenter
            anchors.horizontalCenter: button.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * 0.4
        }
        Text {
            id: outsideWeight
            text: taskModule.pumpOutSideWeight + "g"
            font.pointSize: 28
            anchors.leftMargin: 10
            anchors.left: outsideWeightName.right
            anchors.verticalCenter: outsideWeightName.verticalCenter
        }

        Text {
            id: addWaterName
            text: qsTr("加水量：")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.height * -0.3
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 28
        }

        TextField {
            id: textField
            text: qsTr("")
            anchors.left: addWaterName.right
            anchors.leftMargin: 10
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: addWaterName.verticalCenter
        }

        Text {
            id: addWaterPercentName
            text: qsTr("稀释比例：")
            anchors.top: addWaterName.bottom
            anchors.topMargin: 50
            anchors.horizontalCenter: addWaterName.horizontalCenter
            font.pixelSize: 28
        }

        Text {
            id: addWaterPercent
            text: "0"
            anchors.verticalCenter: addWaterPercentName.verticalCenter
            anchors.leftMargin: 10
            anchors.left: addWaterPercentName.right
            font.pixelSize: 28
        }
    }
}
