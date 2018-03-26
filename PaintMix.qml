import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

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
    }

    TabBar {
        id: paintMixTabBar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        currentIndex: paintMixStackLayout.currentIndex
        TabButton {
                    id: paintMixTabBarMain
                    text: qsTr("Main")
                    anchors.bottom: parent.bottom
                    height: 60
                    background: Rectangle {
                        color: paintMixTabBar.currentIndex === 0 ? "silver" : "#1e90ff"
                    }
                }
                TabButton {
                    id: tabButtonProfile
                    text: qsTr("Profile")
                    anchors.bottom: parent.bottom
                    height: 60
                    background: Rectangle {
                        color: paintMixTabBar.currentIndex === 1 ? "silver" : "#1e90ff"
                    }
                }
                TabButton {
                    id: tabButtonSetting
                    text: qsTr("Setting")
                    anchors.bottom: parent.bottom
                    height: 60
                    background: Rectangle {
                        color: paintMixTabBar.currentIndex === 2 ? "silver" : "#1e90ff"
                    }
                }

                TabButton {
                    id: tabButtonFactory
                    text: qsTr("Factory Mode")
                    anchors.bottom: parent.bottom
                    height: 60
                    background: Rectangle {
                        color: paintMixTabBar.currentIndex === 3 ? "silver" : "#1e90ff"
                    }
                }
    }
}
