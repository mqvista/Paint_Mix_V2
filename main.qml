import QtQuick 2.9
import QtQuick.Controls 2.2
//import QtQuick.VirtualKeyboard 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 800
    title: qsTr("HIWAVE")


    header: ToolBar {
        contentHeight: 60

        ToolButton {
            id: toolButton
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

        Label {
            Text {
                color: "#6678ff"
                text: stackView.currentItem.title
                font.pointSize: 20
            }
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -parent.width * 0.02

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

//    InputPanel {
//        id: inputPanel
//        z: 99
//        x: 0
//        y: window.height
//        width: window.width

//        states: State {
//            name: "visible"
//            when: inputPanel.active
//            PropertyChanges {
//                target: inputPanel
//                y: window.height - inputPanel.height
//            }
//        }
//        transitions: Transition {
//            from: ""
//            to: "visible"
//            reversible: true
//            ParallelAnimation {
//                NumberAnimation {
//                    properties: "y"
//                    duration: 250
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    }
}
