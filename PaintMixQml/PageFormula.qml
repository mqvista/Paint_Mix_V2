import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

Item {
    //////////////////////////////////////////
    //  配方列表的listview                   //
    //  Rectangle里面套一个listview          //
    //  listview 里面套一个component         //
    //  (里面再套一个rectangle 处理文字位置)   //
    //                                     //
    //          Rectange                   //
    //  ||||||||||||||||||||||||||         //
    //  ||      Listview        ||         //
    //  ||   ||||||||||||||||   ||         //
    //  ||   ||  Component ||   ||         //
    //  ||   ||||||||||||||||   ||         //
    //  ||                      ||         //
    //  ||                      ||         //
    //  ||   ||||||||||||||||   ||         //
    //  ||   ||  Component ||   ||         //
    //  ||   ||||||||||||||||   ||         //
    //  ||                      ||         //
    //  ||||||||||||||||||||||||||         //
    //                                     //
    /////////////////////////////////////////
    Rectangle {
        id: formulaListViewRectangle
        width: parent.width / 4
        height: parent.height * 0.98
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 8
        radius: 5
        border.width: 5
        border.color: "Silver"

        ListModel {
            id: tst
            ListElement {
                name: "Alex Wang"
                number: "110"
            }
            ListElement {
                name: "Alex Wang2"
                number: "110"
            }
            ListElement {
                name: "Alex Wang3"
                number: "110"
            }
            ListElement {
                name: "Alex Wang4"
                number: "110"
            }
            ListElement {
                name: "Alex Wang5"
                number: "110"
            }
            ListElement {
                name: "Alex Wang6"
                number: "110"
            }
            ListElement {
                name: "Alex Wang7"
                number: "110"
            }
        }

        //listview的显示布局
        Component{
            id: contactDelegate
            Item {
                height: 100
                width: parent.width
                Rectangle {
                    color: "transparent"
                    width: parent.width * 0.9
                    height: parent.height * 0.9
                    anchors.centerIn: parent
                    Text {
                        text: "Name:" + name
                        font.pointSize: 20
                        anchors.verticalCenter: parent.verticalCenter
                    }

//                    ToolButton {

//                        anchors.verticalCenter: parent.verticalCenter
//                        anchors.right: parent.right
//                        text: "\u274C"
//                        font.pixelSize: Qt.application.font.pixelSize * 2.5
//                        onClicked: {
//                            formulaListView.currentIndex = index
//                        }
//                    }

                    // 删除按钮是由 Rectangle 里面嵌套一个 emoji 组成的
                    // 触发是由mousearea 做触发
                    Rectangle {
                        height: parent.height * 0.6
                        width: parent.width * 0.25
                        color: "transparent"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        Text {
                            id: deleteButtonText
                            anchors.centerIn: parent
                            text: "\u274C"
                            font.pixelSize: Qt.application.font.pixelSize * 2.5
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                formulaListView.currentIndex = index
                                deleteMessageDialog.open()
                            }
                        }

                    }
                }
                //切换触发区域
                MouseArea {
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width * 0.3
                    onClicked: {
                        //切换蓝色选框
                        formulaListView.currentIndex = index
                    }
                }
            }
        }

        ListView {
            id: formulaListView
            width: formulaListViewRectangle.width * 0.9
            anchors.top: formulaListViewRectangle.top
            anchors.bottom: formulaListViewRectangle.bottom
            anchors.topMargin: 8
            anchors.bottomMargin: 8
            anchors.horizontalCenter: formulaListViewRectangle.horizontalCenter
            model: tst
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            highlightMoveDuration: -1
            delegate: contactDelegate
            clip: true
            focus: true
        }
    }

    //确认删除方案的对话框
    MessageDialog {
        id: deleteMessageDialog
        title: "May I have your attention please"
        text: "It's so cool that you are using Qt Quick."
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            console.log("And of course you could only agree.")
        }
        onNo: {
            console.log("And of course you could only agree.")
        }
    }
}
