import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("ScreenResolutions")

    ListModel {
        id: modelScreenResolutions
        ListElement {
            index: 0
            dataName: "abc"
        }
        ListElement {
            index: 1
            dataName: "xyz"
        }
        ListElement {
            index: 2
            dataName: "qqq"
        }
    }

    Rectangle {
        color: "lightgray"
        anchors.fill: parent

        ListView {
            id: lvScreenResolutions
            anchors.fill: parent
            model: modelScreenResolutions
            highlight: Rectangle {
                color: "lightsteelblue"
                radius: 2
            }
            delegate: Item {
                id: me
                width: 100
                height: 30
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        me.ListView.view.currentIndex = index
                    }
                }
                Text {

                    text: dataName
                    anchors.centerIn: parent
                }
            }
        }
    }
}
