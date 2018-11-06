import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Page {
    title: qsTr("Test")
    GridLayout {
        id: gridLayout
        columns: 3
        rows: 3
        anchors.fill: parent

        Rectangle {
            id: rectangle
            width: 300
            height: 70
            color: "#ffffff"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            border.color: "#66CCFF"

            ComboBox {
                id: comboBox
                anchors.left: parent.left
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
                text: qsTr("move")
                anchors.leftMargin: 10
                anchors.left: comboBox.right
                anchors.verticalCenter: parent.verticalCenter
                onReleased: {
                    //console.log(comboBox.currentText)
                    pageSecond.moveAsix(comboBox.currentText)
                }
            }
        }

        Rectangle {
            id: rectangle1
            width: 200
            height: 70
            color: "#ffffff"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            border.color: "#66CCFF"

            Button {
                id: button1
                text: qsTr("GetADCValue")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                focusPolicy: Qt.NoFocus
                onReleased: tttt.start()
            }
            Timer{
                id: tttt
                repeat: true
                interval: 500
                triggeredOnStart: true
                onTriggered: {
                    pageSecond.getExternADCValue()
                }
            }
        }

        Rectangle {
            id: rectangle2
            width: 240
            height: 70
            color: "#ffffff"
            border.color: "#66CCFF"

            Button {
                id: button2
                text: qsTr("抽水")
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                onReleased: pageSecond.openPump()
            }
            Button {
                id: button3
                text: qsTr("取消")
                anchors.left: button2.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                onReleased: pageSecond.closePump()
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
