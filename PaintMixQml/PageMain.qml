import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    Rectangle {
        id: mainRectangle
        width: parent.width / 2
        height: parent.height / 2
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.verticalCenter:  parent.verticalCenter
        radius: 5
        border.width: 5
        border.color: "Silver"

        Button {
            id: button
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("test")
            onClicked: {
                console.log("123");
                taskModule.test();
            }
        }

    }
}
