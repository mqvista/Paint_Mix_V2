import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 800
    title: qsTr("HIWAVE")

    //头栏目， 还有个导航按钮
    header: ToolBar {
        visible: ! indexModule.initialization
        contentHeight: 40

        ToolButton {
            id: toolButton
            anchors.verticalCenter: parent.verticalCenter
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            opacity: 0.8
            font.pixelSize: Qt.application.font.pixelSize * 2.5
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        //头栏目里面的标题
        Label {
            id: tittleLabel
            anchors.centerIn: parent

            //点击次数的flasg
            property int clickFlag: 0
            Text {
                anchors.centerIn: parent
                color: "#6678ff"
                text: stackView.currentItem.title
                font.pointSize: 30
                font.bold: true

                //添加隐藏按键
                //连续按下10下，可进入隐藏菜单
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (stackView.depth == 1)
                        {
                            tittleLabel.clickFlag += 1
                            clickTimer.restart()
                            if (tittleLabel.clickFlag >= 10)
                            {
                                tittleLabel.clickFlag = 0
                                clickTimer.stop()
                                console.log("trage into hidden mode")
                                Qt.quit()
                            }
                        }
                    }
                }
                //给tittleLable的连续按键检测的定时器
                Timer {
                    id: clickTimer
                    interval: 500       //设定500MS
                    repeat: false
                    running: false
                    triggeredOnStart: false
                    onTriggered: {tittleLabel.clickFlag = 0}
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.2
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("PaintMix")
                width: parent.width
                onClicked: {
                    stackView.push("PaintMix.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    property alias stView: stackView
    StackView {
        id: stackView
        initialItem: "HomeForm.qml"
        anchors.fill: parent
    }

    // 全屏覆盖初始化界面
    Rectangle {
        id: initLoadRect
        color: "#66ccff"
        anchors.fill: parent
        visible: indexModule.initialization

        AnimatedImage
        {
            anchors.centerIn: parent
            source: "./img/loading.gif"
            scale: 0.2
            playing: indexModule.initialization
            // tmp use
            onPlayingChanged: {
                stackView.push("PaintMix.qml")
            }
        }

        Text {
            id: ttt
            anchors.centerIn: parent
            anchors.verticalCenterOffset: parent.height * 0.2
            text: qsTr("Loading")
            font.pixelSize: Qt.application.font.pixelSize * 3
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }
}
