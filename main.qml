import QtQuick
import QtQuick.Controls
import Qt.labs.settings 1.0

Window {
    id: window
    width: 300
    height: 380
    visible: true
    title: qsTr("fitmat 20220606")
    
    property string normalId: ""
    property string gameId: ""

    function reloadDisplay() {
        modelScreenResolutions.clear()
        let displays = display.getSettings(1)
        let idx = 0
        let currentSelectIdx = -1;
        for (let it of displays) {
            it.index = idx++
            if (it.current) {
                currentSelectIdx = it.index
                if (!normalId) {
                    normalId = it.id
                }
            }
            modelScreenResolutions.append(it)
        }
        if (currentSelectIdx!=-1) {
            lvScreenResolutions.currentIndex = currentSelectIdx
        }
    }

    function autoSwitchDisplay() {
        let curData = modelScreenResolutions.get(lvScreenResolutions.currentIndex)
        let nextId = null
        if (curData.id === normalId) {
            nextId = gameId
        } else {
            nextId = normalId
        }
        if (nextId) {
            let r = display.applySetting(nextId)
            return r === 0
        }
        return false
    }

    Component.onCompleted: {
        reloadDisplay()
        if (autoSwitchDisplay()) {
            reloadDisplay()
        }
        if (parseInt(autoExit) === 1) {
            Qt.quit()
        }
    }

    ListModel {
        id: modelScreenResolutions
    }

    Rectangle {
        color: "white"
        anchors.fill: parent

        
        ListView {
            id: lvScreenResolutions
            anchors.fill: parent
            model: modelScreenResolutions
            boundsBehavior: Flickable.StopAtBounds
            highlightMoveDuration: 10
            highlightResizeDuration: 0
            interactive: true
            keyNavigationEnabled: true
            keyNavigationWraps: true
            focus: true
            ScrollBar.vertical: ScrollBar{ }

            Keys.onPressed: event => {
                if (event.key === Qt.Key_F5) {
                    reloadDisplay();
                } else if (event.key === Qt.Key_Escape) {
                    Qt.quit()
                }
            }

            highlight: Rectangle {
                color: "#3296FA"
                radius: 2
            }

            delegate: Item {
                width: ListView.view.width
                height: 30
         
                Text {
                    id: tvResolution
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: model.current
                    text: (() => {
                        let s = `${model.width} x ${model.height}\t(${model.freq})  `
                        if (model.id === normalId) {
                            s += "[??????]"
                        }
                        if (model.id === gameId) {
                            s += "[??????]"
                        }
                        if (model.current) {
                            s += "(????????????)"
                        }
                        return s
                    })()
                }
                
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onDoubleClicked: {
                        window.applySetting()
                    }

                    onClicked: mouse => {
                        lvScreenResolutions.currentIndex = model.index
                        if (mouse.button === Qt.RightButton) {
                            contextMenu.popup()
                        }
                    }
                }
            }
        }
    }

    function applySetting() {
        let data = modelScreenResolutions.get(lvScreenResolutions.currentIndex)
        let r = display.applySetting(data.id)
        if (r === 0) {
            reloadDisplay()
        }
    }
    
    Menu{
        id: contextMenu
        
        MenuItem{
            text: "????????????"
            onClicked: {
                window.applySetting()
            }
        }
        
        MenuItem{
            text: "????????????"
            onClicked: {
                let data = modelScreenResolutions.get(lvScreenResolutions.currentIndex)
                if (data.id) {
                    settings.normalId = data.id
                }
            }
        }
        
        MenuItem{
            text: "????????????"
            onClicked: {
                let data = modelScreenResolutions.get(lvScreenResolutions.currentIndex)
                if (data.id) {
                    settings.gameId = data.id
                }
            }
        }
        
        MenuItem{
            text: "????????????"
            onClicked: {
                reloadDisplay()
            }
        }
    }
    
    Settings{
        id: settings
        category: "default"
        fileName: "default.config"
        property alias normalId: window.normalId
        property alias gameId: window.gameId
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }
}
