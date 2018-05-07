import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

Item {
    id: item1

    // 新增加的添加参数的对话框
    NewFormulaDialog {
        id: newFormula
    }



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
        width: parent.width * 0.25
        height: parent.height * 0.98
        //anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        radius: 5
        border.width: 5
        border.color: "Silver"

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
                        text: "配方名称: " + name
                        font.pointSize: Qt.application.font.pixelSize * 2
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    // 删除按钮是由 Rectangle 里面嵌套一个 image 组成的
                    // 触发是由mousearea 做触发
                    Rectangle {
                        height: parent.height * 0.6
                        width: parent.width * 0.25
                        color: "transparent"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        Image {
                            source: "../img/cross.png"
                            anchors.centerIn: parent
                            scale: 0.2
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                // 点击后刷新listview, 用于跟新highLight 和 index
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
                        // 点击后刷新listview, 用于跟新highLight 和 index
                        formulaListView.currentIndex = index
                        // 用于刷新 对应的 gridview
                        formulaGrid.reflushUseName(name);
                    }
                }
            }
        }

        //ListView to show data
        ListView {
            id: formulaListView
            width: formulaListViewRectangle.width * 0.9
            boundsBehavior: Flickable.StopAtBounds
            anchors.top: formulaListViewRectangle.top
            anchors.bottom: formulaListViewRectangle.bottom
            anchors.topMargin: 8
            anchors.bottomMargin: 8
            anchors.horizontalCenter: formulaListViewRectangle.horizontalCenter
            model: formulaList
            highlight: Rectangle { color: "lightsteelblue"; radius: 5; opacity: 0.5 }
            highlightMoveDuration: -1
            delegate: contactDelegate
            clip: true
            focus: true
            // listview 加载完成后 加载 gridview 内的数据
            Component.onCompleted: {
                // 先从formulaList 用index 换 name， 然后在用name 去刷新 gridView
                formulaGrid.reflushUseName(formulaList.getNameUseIndex(currentIndex))
            }
        }

        //确认删除方案的对话框
        MessageDialog {
            id: deleteMessageDialog
            title: "May I have your attention please"
            text: "确认删除当前参数 ？？？？"
            icon: StandardIcon.Question
            standardButtons: StandardButton.Yes | StandardButton.No
            onYes: {
                formulaList.removeWithXML(formulaListView.currentIndex)
            }
        }
    }


    //////////////////////////
    //
    //  界面显示详细的grid view
    //
    //  先设定一个包围的外框
    //
    //////////////////////////
    Rectangle
    {
        id: formulaGridViewRectangle
        width: parent.width * 0.73
        height: parent.height * 0.6
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
        radius: 5
        border.width: 5
        border.color: "Silver"

        Component {
            id: gridViewDelegate
            Item {
                height: formulaGridView.cellHeight
                width: formulaGridView.cellWidth
                Rectangle {
                    color: "transparent"
                    width: parent.width * 0.9
                    height: parent.height * 0.9
                    anchors.centerIn: parent
                    border.color: "black"
                    radius: 5

                    Column {
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 8
                            text: "名称: " + name
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                        }
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 8
                            text: "设定: " + setValue
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                        }
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 8
                            text: "实际: " + realValue
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                        }
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 8
                            text: "位置: " + addLocal
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                        }
                    }



                }
            }
        }
        GridView {
            id: formulaGridView
            cellWidth: parent.width * 0.24
            cellHeight: parent.height * 0.3
            width: formulaGridViewRectangle.width
            height: formulaGridViewRectangle.height

            ///////
            anchors.top: formulaGridViewRectangle.top
            anchors.bottom: formulaGridViewRectangle.bottom
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            anchors.left: formulaGridViewRectangle.left
            anchors.right: formulaGridViewRectangle.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            ///////

            model: formulaGrid
            highlight: Rectangle { color: "lightsteelblue"; radius: 5; opacity: 0.5}
            highlightMoveDuration: -1
            delegate: gridViewDelegate
            clip: true
            focus: true
        }
    }

    Button {
        id: button
        text: qsTr("新增方案")
        anchors.top: formulaGridViewRectangle.bottom
        anchors.topMargin: 30
        anchors.right: formulaListViewRectangle.left
        anchors.rightMargin: 30
        onClicked: {
            formulaAddNew.reflush()
            // 开启对话框，添加新的方案
            newFormula.open()
            // 设定新增方案对话框的位置 x 在中间 y 在中间靠上
            newFormula.x = parent.width / 2 - newFormula.width / 2
            newFormula.y = parent.height / 2 - newFormula.height / 1.5
        }
    }
}
