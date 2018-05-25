import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
//import QtQuick.VirtualKeyboard 2.2

Popup {
    id: popupDialog
    width: parent.width / 1.2
    height: parent.height / 1.2
    modal: true
    focus: true
    // 按 ESC 关闭
    closePolicy: Popup.OnEscape
    background: bkRect


    // 丢一个 rectangle 东西都放里面
    Rectangle {
        id: bkRect
        width: parent.width
        height: parent.height
        border.width: 2
        opacity: 1
        radius: 8

        // 头和标题
        Rectangle {
            id: tittleHeader
            width: parent.width
            height: parent.height * 0.08
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#66ccff"
            clip: true

            Text {
                text: qsTr("新增配色方案")
                font.pointSize: Qt.application.font.pixelSize * 1.5
                anchors.centerIn: parent
            }
            // 设置标题为可拖动整个窗口
            MouseArea {
                property point clickPoint: "0, 0"
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onPressed: {
                    clickPoint = Qt.point(mouse.x, mouse.y)
                }
                onPositionChanged: {
                    var offset = Qt.point(mouse.x - clickPoint.x, mouse.y - clickPoint.y)
                    setDlgPoint(offset.x, offset.y);
                }
            }
        }

        // 放一个 ListView 里面存放新的方案的详细信息
        Rectangle {
            id: addFormulaListViewRectangle
            width: parent.width * 0.98
            height: parent.height * 0.7
            border.color: "#150000"
            anchors.top: tittleHeader.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter

            // listView 的视图模型
            Component {
                id: addFormulaDelegate
                Item {
                    id: componetItem
                    height: 60
                    width: parent.width
                    Rectangle {
                        id: dragRect
                        width: parent.width * 0.98
                        height: parent.height * 0.8
                        border.color: "black"
                        radius: 8
                        anchors.centerIn: parent
                        // 第一个套装
                        Text {
                            id: motionText
                            text: "动作: "
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                        }
                        ComboBox {
                            id: motionComboBox
                            width: 82
                            height: 35
                            model: ListModel {
                                ListElement {text: "注液"}
                                ListElement {text: "注水"}
                                ListElement {text: "移液"}
                            }
                            font.pointSize: Qt.application.font.pixelSize * 1.2
                            currentIndex: -1
                            anchors.left: motionText.right
                            anchors.verticalCenter: parent.verticalCenter
                            onCurrentIndexChanged: {
                                if (currentIndex == 0)
                                {
                                    ItemName = "Motor"
                                }
                                if (currentIndex == 1)
                                {
                                    ItemName = "Water";
                                }
                                if (currentIndex == 2)
                                {
                                    ItemName = "Exchange";
                                }
                                // 更新百分比
                                formulaAddNew.updatePercent();
                            }
                        }
                        // 第二个套装
                        Text {
                            id: motorText
                            visible: motionComboBox.currentText != "移液" && motionComboBox.currentText != "注水"
                            text: "轴号: "
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: motionComboBox.right
                            anchors.leftMargin: 5
                        }
                        ComboBox {
                            id: motorComboBox
                            visible: motionComboBox.currentText != "移液" && motionComboBox.currentText != "注水"
                            width: 82
                            height: 35
                            model: ListModel {
                                ListElement {text: "1"}
                                ListElement {text: "2"}
                                ListElement {text: "3"}
                                ListElement {text: "4"}
                                ListElement {text: "5"}
                                ListElement {text: "6"}
                                ListElement {text: "7"}
                                ListElement {text: "8"}
                                ListElement {text: "9"}
                                ListElement {text: "10"}
                            }
                            font.pointSize: Qt.application.font.pixelSize * 1.2
                            currentIndex: -1
                            anchors.left: motorText.right
                            anchors.verticalCenter: parent.verticalCenter
                            onCurrentIndexChanged: {
                                MotorNum = motorComboBox.currentIndex + 1
                            }
                        }


                        // 第三个套装
                        Text {
                            id: localName
                            visible: motionComboBox.currentText != "移液"
                            text: "方位: "
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: motorComboBox.right
                            anchors.leftMargin: 5
                        }
                        ComboBox {
                            id: localComboBox
                            visible: motionComboBox.currentText != "移液"
                            width: 82
                            height: 35
                            model: ListModel {
                                ListElement {text: "小秤"}
                                ListElement {text: "大秤"}
                            }
                            font.pointSize: Qt.application.font.pixelSize * 1.2
                            currentIndex: -1
                            anchors.left: localName.right
                            anchors.verticalCenter: parent.verticalCenter
                            onCurrentIndexChanged: {
                                if (currentIndex == 0)
                                {
                                    AddLocal = "1"
                                }
                                if (currentIndex == 1)
                                {
                                    AddLocal = "2";
                                }
                            }
                        }

                        // 第四个套装
                        Text {
                            id: weightName
                            visible: motionComboBox.currentText != "移液"
                            text: "重量: "
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: localComboBox.right
                            anchors.leftMargin: 5
                        }
                        TextField {
                            id: weightTextField
                            visible: motionComboBox.currentText != "移液"
                            anchors.left: weightName.right
                            anchors.verticalCenter: parent.verticalCenter
                            width: 80
                            font.pointSize: Qt.application.font.pixelSize * 1.2
                            validator: IntValidator {bottom: 1; top: 999;}
                            inputMethodHints: Qt.ImhDigitsOnly
                            onEditingFinished: {
                                SetWeight = text

                                // 更新百分比
                                formulaAddNew.updatePercent();
                            }
                            onPressed: {
                                        vkb.visible = true; //当选择输入框的时候才显示键盘
                                    }
                        }

                        // 第五个套装
                        Text {
                            id: percentName
                            visible: motionComboBox.currentText != "移液"
                            text: "比重: "
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: weightTextField.right
                            anchors.leftMargin: 5
                        }
                        Text {
                            id: percentText
                            visible: motionComboBox.currentText != "移液"
                            text: Percent
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: percentName.right
                            anchors.leftMargin: 5
                        }

                        //第N个开关
                        Rectangle {
                            id: closeRec
                            height: parent.height * 0.9
                            width: parent.height * 0.9
                            border.color: "transparent"
                            anchors.right: addRec.left
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            Image {
                                source: "../img/close.png"
                                anchors.centerIn: parent
                                scale: 0.2
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (addFormulaListView.count >1 )
                                    {
                                        formulaAddNew.removeRows(index, 1)
                                        // 更新百分比
                                        formulaAddNew.updatePercent();
                                    }
                                }
                            }
                        }

                        //第N个开关
                        Rectangle {
                            id: addRec
                            height: parent.height * 0.9
                            width: parent.height * 0.9
                            border.color: "transparent"
                            anchors.right: swapRec.left
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            Image {
                                source: "../img/add.png"
                                anchors.centerIn: parent
                                scale: 0.2
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    //onsole.log(index)
                                    formulaAddNew.insertRows(index + 1, 1)
                                }
                            }
                        }

                        //第N个开关
                        Rectangle {
                            id: swapRec
                            height: parent.height * 0.9
                            width: parent.height * 0.9
                            border.color: "transparent"
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            Image {
                                source: "../img/upDown.png"
                                anchors.centerIn: parent
                                scale: 0.2
                            }
                            MouseArea {
                                id: mouseArea
                                anchors.fill: parent
                                //drag.target: swapRec
                                //drag.axis: Drag.YAxis
                                onMouseYChanged: {
                                    //console.log(MouseArea.mouseY + componetItem.y)
                                    var targetDrag = addFormulaListView.indexAt(mouseArea.mouseX + componetItem.x, mouseArea.mouseY + componetItem.y)
                                    if (index !== targetDrag)
                                    {
                                        if (targetDrag !== -1)
                                        {
                                            console.log("oldINdex=", index)
                                            console.log("target=", targetDrag)
                                            formulaAddNew.move(index, targetDrag)
                                        }
                                    }
                                }
                            }
                         }
                    }
                }
            }

            ListView {
                id: addFormulaListView
                width: addFormulaListViewRectangle.width * 0.98
                boundsBehavior: Flickable.StopAtBounds
                anchors.top: addFormulaListViewRectangle.top
                anchors.bottom: addFormulaListViewRectangle.bottom
                anchors.topMargin: 8
                anchors.bottomMargin: 8
                anchors.horizontalCenter: addFormulaListViewRectangle.horizontalCenter
                model: formulaAddNew
                highlight: Rectangle { color: "lightsteelblue"; radius: 5; opacity: 0.5 }
                highlightMoveDuration: -1
                delegate: addFormulaDelegate
                clip: true
                focus: true
                move: Transition {
                    NumberAnimation {properties: "x, y"; duration: 200}
                }
            }
        }

        Rectangle {
            id: bottomTail
            width: parent.width * 0.98
            height: parent.height * 0.14
            anchors.top: addFormulaListViewRectangle.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            border.color: "black"
            clip: true

            Text {
                id: formulaName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 20
                font.pointSize: Qt.application.font.pixelSize * 1.5
                text: qsTr("方案名称: ")
            }
            TextField {
                id: formulaNameTextField
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: formulaName.right
                anchors.leftMargin: 10
                width: 150
                font.pointSize: Qt.application.font.pixelSize * 1.5
                onPressed: {
                            vkb.visible = true; //当选择输入框的时候才显示键盘
                        }
            }

            Text {
                id: totalWeightText
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: formulaNameTextField.right
                anchors.leftMargin: 20
                font.pointSize: Qt.application.font.pixelSize * 1.5
                text: qsTr("总重量:")
            }
            Text {
                id: totalWeightValue
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: totalWeightText.right
                anchors.leftMargin: 10
                font.pointSize: Qt.application.font.pixelSize * 1.5
                text: formulaAddNew.totalWeight
            }





            Text {
                id: warningText
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: totalWeightValue.right
                anchors.leftMargin: 20
                font.pointSize: Qt.application.font.pixelSize * 1.5
                color: "red"
                text: qsTr("")
            }

            Button {
                id: saveButton
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 20
                text: qsTr("保存新方案")
                onClicked: {
                    if (formulaName.text !== "")
                    {
                        if (formulaAddNew.saveFormula(formulaNameTextField.text))
                        {
                            formulaNameTextField.text = ""
                            formulaList.reflushAll()
                            popupDialog.close()
                            return;
                        }
                    };
                    // 显示错误警告文字，然后定时器定时
                    warningText.text = "请检查名称或参数是否冲突或遗漏 ！"
                    clearTextTimer.start()
                }
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: saveButton.left
                anchors.margins: 10
                anchors.rightMargin: 20
                text: qsTr("关闭窗口")
                onClicked: {
                    popupDialog.close()
                }
            }

            Timer {
                id: clearTextTimer
                interval: 2000
                repeat: false
                running: false
                triggeredOnStart: false
                onTriggered: {
                    warningText.text = ""
                }
            }
        }

        /*InputPanel {
            id: vkb
            visible: false
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            //这种集成方式下点击隐藏键盘的按钮是没有效果的，
            //只会改变active，因此我们自己处理一下
            onActiveChanged: {
                if(!active) { visible = false; }
                }
           }*/

    }




    // 用偏移量计算最终 Popup 的位置
    function setDlgPoint(dlgX ,dlgY){
        //设置窗口拖拽不能超过父窗口
        if(popupDialog.x + dlgX < 0)
        {
            popupDialog.x = 0
        }
        else if(popupDialog.x + dlgX > popupDialog.parent.width - popupDialog.width)
        {
            popupDialog.x = popupDialog.parent.width - popupDialog.width
        }
        else
        {
            popupDialog.x = popupDialog.x + dlgX
        }
        if(popupDialog.y + dlgY < 0)
        {
            popupDialog.y = 0
        }
        else if(popupDialog.y + dlgY > popupDialog.parent.height - popupDialog.height)
        {
            popupDialog.y = popupDialog.parent.height - popupDialog.height
        }
        else
        {
            popupDialog.y = popupDialog.y + dlgY
        }
    }
}
