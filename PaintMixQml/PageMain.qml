import QtQuick 2.0
import QtQuick.Controls 2.3
//import QtQuick.VirtualKeyboard 2.2


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
            height: 40
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
            text: taskModule.pumpOutSideWeight
            font.pointSize: 28
            anchors.leftMargin: 10
            anchors.left: outsideWeightName.right
            anchors.verticalCenter: outsideWeightName.verticalCenter
        }

        Text {
            id: outsideG
            text: "g"
            font.pointSize: 28
            anchors.leftMargin: 10
            anchors.left: outsideWeight.right
            anchors.verticalCenter: outsideWeight.verticalCenter
        }

        Text {
            id: addWaterName
            text: qsTr("加水量:")
            anchors.left: button.left
            //anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: parent.width * -0.05
            font.pixelSize: 28
        }

        TextField {
            id: textField
            width: 100
            height: 40
            text: qsTr("")
            anchors.left: addWaterName.right
            anchors.leftMargin: 10
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: addWaterName.verticalCenter
            validator: IntValidator {bottom: 1; top: 999;}
            inputMethodHints: Qt.ImhDigitsOnly
            font.pointSize: 28
            onEditingFinished: {
                addWaterPercent.text = (outsideWeight.text * 1) / (textField.text * 1)
            }
            onPressed: {
                        vkb.visible = true; //当选择输入框的时候才显示键盘
                    }
        }

        Text {
            id: addWaterLable
            text: qsTr("L")
            anchors.leftMargin: 10
            anchors.left: textField.right
            anchors.verticalCenter: textField.verticalCenter
            font.pixelSize: 28
        }

        Text {
            id: addWaterPercentName
            text: qsTr("稀释比例:")
            anchors.left: button.left
            anchors.top: addWaterName.bottom
            anchors.topMargin: 50
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

        Text {
            id: addWaterPercentLable
            text: "%"
            anchors.leftMargin: 5
            anchors.verticalCenter: addWaterPercentName.verticalCenter
            anchors.left: addWaterPercent.right
            font.pixelSize: 28
        }

        Button {
            id: button1
            y: 180
            height: 40
            text: qsTr("加水")
            font.pointSize: 28
            anchors.verticalCenterOffset: 0
            anchors.left: textField.right
            anchors.leftMargin: 60
            anchors.verticalCenter: addWaterName.verticalCenter
            enabled: !taskModule.busy
            onClicked: {
                taskModule.addWaterOutside(textField.text)
            }
        }
    }


//    InputPanel {
//        id: vkb
//        visible: false
//        anchors.right: parent.right
//        anchors.left: parent.left
//        anchors.bottom: parent.bottom
//        //这种集成方式下点击隐藏键盘的按钮是没有效果的，
//        //只会改变active，因此我们自己处理一下
//        onActiveChanged: {
//            if(!active) { visible = false; }
//            }
//       }

}
