import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Popup {
    id: popupAdditionDialog
    width: parent.width / 1.2
    height: parent.height / 1.5
    modal: true
    focus: true
    // 按 ESC 关闭
    closePolicy: Popup.OnEscape
    background: bkRect


    // 丢一个 rectangle 东西都放里面
    Rectangle {
        id: bkRect
        anchors.fill: parent
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
                text: qsTr("微调配色方案")
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
            id: additionFormulaListViewRectangle
            width: parent.width * 0.98
            height: parent.height * 0.7
            border.color: "#150000"
            anchors.top: tittleHeader.bottom
            anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

            // listView 的视图模型
            Component {
                id: additionFormulaDelegate
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
                            text: "动作:"
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                        }
                        Text {
                            id: motionValue
                            text: {
                                if (ItemName == "Motor")
                                    return "注液"
                                if (ItemName == "Water")
                                    return "注水"
                                if (ItemName == "PumpScaleOutside")
                                    return "移液"
                                if (ItemName == "AdditionPaint")
                                    return "泵液"
                            }
                            font.underline: true
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.left: motionText.right
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        // 第二个套装
                        Text {
                            id: motorText
                            text: "编号:"
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: motionText.right
                            anchors.leftMargin: parent.width * 0.05
                        }
                        Text {
                            id: motorValue
                            text: MotorNum
                            font.underline: true
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.left: motorText.right
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        // 第三个套装
                        Text {
                            id: localText
                            text: "方位:"
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: motorText.right
                            anchors.leftMargin: parent.width * 0.02
                        }
                        Text {
                            id: localValue
                            text: {
                                if (AddLocal == '1')
                                    return "小秤"
                                if (AddLocal == '2')
                                    return "大秤"
                                if (AddLocal == '3')
                                    return "中桶"
                            }
                            font.underline: true
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.left: localText.right
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        // 第四个套装
                        Text {
                            id: weightText
                            text: "重量:"
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: localText.right
                            anchors.leftMargin: parent.width * 0.06
                        }
                        Text {
                            id: weightValue
                            text: SetWeight + "G"
                            font.underline: true
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.left: weightText.right
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        // 第五个套装
                        Text {
                            id: percentText
                            text: "比重:"
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: weightText.right
                            anchors.leftMargin: parent.width * 0.06
                        }
                        Text {
                            id: percentValue
                            text: Percent + "%"
                            font.underline: true
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.left: percentText.right
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        // 设定偏移量
                        Text {
                            id: offsetText
                            text: "偏移量: "
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: percentText.right
                            anchors.leftMargin: parent.width * 0.09
                        }
                        SpinBox {
                            property int decimals: 1
                            property real realValue: value / 100
                            id: offsetValue
                            enabled: {
                                if (ItemName == "PumpScaleOutside")
                                    return false;
                                else
                                    return true;
                            }
                            width: 120
                            value: 0
                            from: parseInt(weightValue.text) * -10
                            to: parseInt(weightValue.text) * 10
                            stepSize: 1
                            anchors.left: offsetText.right
                            anchors.verticalCenter: parent.verticalCenter
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            onValueChanged: {
                                Offset = value
                                formulaAddition.reflushOffsetPercent()
                            }
                            validator: DoubleValidator {
                                bottom: Math.min(offsetValue.from, offsetValue.to)
                                top: Math.max(offsetValue.from, offsetValue.to)
                            }
                            textFromValue: function(value, locale){
                                return Number(value / 10).toLocaleString(locale, 'f', offsetValue.decimals)
                            }
                            valueFromText: function(text, locale) {
                                return Number.fromLocaleString(locale, text) * 10
                            }
                        }

                        // 显示偏移比例
                        Text {
                            id: offsetPercent
                            text: "偏移后比例: "
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: offsetText.right
                            anchors.leftMargin: parent.width * 0.16
                        }
                        Text {
                            id: offsetPercentValue
                            text: OffsetPercent + "%"
                            font.underline: true
                            font.pointSize: Qt.application.font.pixelSize * 1.5
                            anchors.left: offsetPercent.right
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
            }

            ListView {
                id: additionFormulaListView
                width: additionFormulaListViewRectangle.width * 0.98
                boundsBehavior: Flickable.StopAtBounds
                anchors.top: additionFormulaListViewRectangle.top
                anchors.bottom: additionFormulaListViewRectangle.bottom
                anchors.topMargin: 8
                anchors.bottomMargin: 8
                anchors.horizontalCenter: additionFormulaListViewRectangle.horizontalCenter
                model: formulaAddition
                highlight: Rectangle { color: "lightsteelblue"; radius: 5; opacity: 0.5 }
                highlightMoveDuration: -1
                delegate: additionFormulaDelegate
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
            anchors.top: additionFormulaListViewRectangle.bottom
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
            Text {
                id: formulaNameTextField
                text: formulaList.getNameUseIndex(formulaListView.currentIndex)
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: formulaName.right
                anchors.leftMargin: 10
                width: 150
                font.pointSize: Qt.application.font.pixelSize * 1.5
            }

            Text {
                id: warningText
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: formulaNameTextField.right
                anchors.leftMargin: 20
                font.pointSize: Qt.application.font.pixelSize * 1.5
                color: "red"
                text: qsTr("")
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 20
                text: qsTr("运行微调方案")
                onClicked: {
                    formulaAddition.runAndSaveFixedFormula(formulaList.getNameUseIndex(formulaListView.currentIndex))
                    popupAdditionDialog.close()
                    // TODO 更新界面的修改 有问题
                    //formulaGrid.reflushUseName(formulaList.getNameUseIndex(formulaListView.currentIndex));

                }
            }
        }
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
