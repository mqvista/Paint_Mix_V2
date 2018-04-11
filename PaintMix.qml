import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "./PaintMixQml"      //导入文件夹内，使得内部qml可以访问到

Page {
//    width: 600
//    height: 400

    title: qsTr("颜料配色")

    StackLayout {
        id: paintMixStackLayout
        anchors.top:parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: paintMixTabBar.top
        currentIndex: paintMixTabBar.currentIndex

        //一号QML
        PageFormula{

        }
    }

    TabBar {
        id: paintMixTabBar
        height: 60
        currentIndex: 0
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        TabButton {
                    id: paintMixTabBarMain
                    text: qsTr("Main")
                    font.pointSize: 30
                    autoExclusive: false
                    anchors.bottom: parent.bottom
                    height: parent.height
                    background: Rectangle {
                        color: paintMixTabBar.currentIndex === 0 ? "silver" : "#1e90ff"
                    }
                }
                TabButton {
                    id: tabButtonProfile
                    text: qsTr("Profile")
                    font.pointSize: 30
                    anchors.bottom: parent.bottom
                    height: parent.height
                    background: Rectangle {
                        color: paintMixTabBar.currentIndex === 1 ? "silver" : "#1e90ff"
                    }
                }
                TabButton {
                    id: tabButtonSetting
                    text: qsTr("Setting")
                    font.pointSize: 30
                    anchors.bottom: parent.bottom
                    height: parent.height
                    background: Rectangle {
                        color: paintMixTabBar.currentIndex === 2 ? "silver" : "#1e90ff"
                    }
                }

                TabButton {
                    id: tabButtonFactory
                    text: qsTr("Factory Mode")
                    font.pointSize: 30
                    anchors.bottom: parent.bottom
                    height: parent.height
                    background: Rectangle {
                        color: paintMixTabBar.currentIndex === 3 ? "silver" : "#1e90ff"
                    }
                }
    }
}