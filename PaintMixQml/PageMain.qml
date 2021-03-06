import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    id: item1
    property bool middleTankAddWaterFlag: false;
    property bool middleTankPumpToOutsideFlag: false;
    property bool middleTankMixFlag: false;
    property bool scaleSmallPumpToOutsideFlag: false;
    property bool scaleBigPumpToOutsideFlag: false;

    Rectangle {
        id: mainRectangle
        width: parent.width / 1.2
        height: parent.height / 1.2
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.verticalCenter:  parent.verticalCenter
        radius: 5
        border.width: 5
        border.color: "Silver"

        GridLayout {
            id: gridLayout
            columns: 1
            rows: 5
            anchors.fill: parent

            Rectangle {
                id: rectangle
                implicitWidth: 500
                implicitHeight: 70
                color: "#ffffff"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.color: "black"
                border.width: 3

                Text {
                    id: nameMoveAsix
                    text: qsTr("移动转盘:")
                    anchors.leftMargin: 10
                    font.pointSize: Qt.application.font.pixelSize * 2
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }


                ComboBox {
                    id: nameComboBox
                    anchors.left: nameMoveAsix.right
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    model: ListModel {
                        ListElement {
                            text: "1"
                        }
                        ListElement {
                            text: "2"
                        }
                        ListElement {
                            text: "3"
                        }
                        ListElement {
                            text: "4"
                        }
                        ListElement {
                            text: "5"
                        }
                        ListElement {
                            text: "6"
                        }
                        ListElement {
                            text: "7"
                        }
                        ListElement {
                            text: "8"
                        }
                        ListElement {
                            text: "9"
                        }
                        ListElement {
                            text: "10"
                        }
                    }
                }

                Button {
                    id: button
                    text: qsTr("运行")
                    enabled: !taskModule.busy
                    anchors.leftMargin: 10
                    anchors.left: nameComboBox.right
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        pageSecond.moveAsix(nameComboBox.currentText)
                    }
                }
            }

            Rectangle {
                id: rectangle1
                implicitWidth: 500
                implicitHeight: 70
                color: "#ffffff"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.color: "black"
                border.width: 3

                Button {
                    id: buttonOpenMiddleTankToUserTank
                    text: qsTr("开启中桶抽水泵")
                    enabled: !taskModule.busy
                    anchors.leftMargin: 10
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    focusPolicy: Qt.NoFocus
                    onReleased:
                    {
                        middleTankPumpToOutsideFlag = true;
                        pageSecond.openMiddleTankToOutsidePump();
                    }

                }
                Button {
                    id: buttonCloseMiddleTankToUserTank
                    text: qsTr("关闭中桶抽水泵")
                    enabled: taskModule.busy && middleTankPumpToOutsideFlag
                    anchors.leftMargin: 10
                    anchors.left: buttonOpenMiddleTankToUserTank.right
                    anchors.verticalCenter: parent.verticalCenter
                    focusPolicy: Qt.NoFocus
                    onReleased:
                    {
                        pageSecond.closeMiddleTankToOutsidePump()
                        middleTankPumpToOutsideFlag = false;
                    }
                }
                Text {
                    id: nameMiddleTank
                    text: qsTr("中桶读数:")
                    anchors.left: buttonCloseMiddleTankToUserTank.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: Qt.application.font.pixelSize * 2
                }
                Text {
                    text: taskModule.middleTankLevel
                    anchors.left: nameMiddleTank.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: Qt.application.font.pixelSize * 2
                }
            }

            Rectangle {
                id: rectangle2
                implicitWidth: 500
                implicitHeight: 70
                color: "#ffffff"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.color: "black"
                border.width: 3



                Button {
                    id: buttonOpenMiddleTankAddWater
                    text: qsTr("中桶开启加水")
                    enabled: !taskModule.busy
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        middleTankAddWaterFlag = true;
                        pageSecond.openMiddleTankAddWaterPump();
                    }

                }
                Button {
                    id: buttonCloseMiddleTankAddWater
                    text: qsTr("中桶关闭加水")
                    enabled: taskModule.busy && middleTankAddWaterFlag == true
                    anchors.left: buttonOpenMiddleTankAddWater.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        pageSecond.closeMiddleTankAddWaterPump()
                        middleTankAddWaterFlag = false;
                    }
                }

                Button {
                    id: buttonOpenMiddleTankMix
                    text: qsTr("中桶开启混合")
                    enabled: !taskModule.busy
                    anchors.left: buttonCloseMiddleTankAddWater.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        pageSecond.openMiddleTankMix()
                        middleTankMixFlag = true
                    }
                }

                Button {
                    id: buttonCloseMiddleTankMix
                    text: qsTr("中桶关闭混合")
                    enabled: taskModule.busy && middleTankMixFlag == true
                    anchors.left: buttonOpenMiddleTankMix.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        pageSecond.closeMiddleTankMix()
                        middleTankMixFlag = false;
                    }
                }

            }

            Rectangle {
                id: rectangle3
                implicitWidth: 500
                implicitHeight: 70
                color: "#ffffff"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.color: "black"
                border.width: 3

                Button {
                    id: buttonOpenSmallScalePumpToOutSide
                    text: qsTr("开启小秤抽出")
                    enabled: !taskModule.busy
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        scaleSmallPumpToOutsideFlag = true
                        pageSecond.openSmallScalePumpToOutSide()
                    }
                }

                Button {
                    id: buttonCloseSmallScalePumpToOutSide
                    text: qsTr("关闭小秤抽出")
                    enabled: taskModule.busy && scaleSmallPumpToOutsideFlag == true
                    anchors.left: buttonOpenSmallScalePumpToOutSide.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        scaleSmallPumpToOutsideFlag = false
                        pageSecond.closeSmallScalePumpToOutSide()
                    }
                }

                Button {
                    id: buttonOpenBigScalePumpToOutSide
                    text: qsTr("开启大秤抽出")
                    enabled: !taskModule.busy
                    anchors.left: buttonCloseSmallScalePumpToOutSide.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        scaleBigPumpToOutsideFlag = true
                        pageSecond.openBigScalePumpToOutSide()
                    }
                }

                Button {
                    id: buttonCloseBigScalePumpToOutSide
                    text: qsTr("关闭大秤抽出")
                    enabled: taskModule.busy && scaleBigPumpToOutsideFlag == true
                    anchors.left: buttonOpenBigScalePumpToOutSide.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        scaleBigPumpToOutsideFlag = false
                        pageSecond.closeBigScalePumpToOutSide()
                    }
                }
            }

            Rectangle {
                id: rectangle4
                implicitWidth: 500
                implicitHeight: 70
                color: "#ffffff"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                border.color: "black"
                border.width: 3



                Button {
                    id: buttonSystemReboot
                    text: qsTr("系统重启")
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        taskModule.systemReboot()
                    }

                }
                Button {
                    id: buttonSystemShutdown
                    text: qsTr("系统关机")
                    anchors.left: buttonSystemReboot.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    onReleased: {
                        taskModule.systemShutdown()
                    }
                }
            }
        }
    }
}
/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
