import QtQuick 2.12
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.12

import "entity"

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 480
    title: qsTr("puzzler")
    menuBar: MenuBar{
        Menu{
            title: qsTr("File")
            MenuItem{
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }



    toolBar: ToolBar{
        ToolButton{
            iconSource: "qrc:/images/kitbuttons/open.png"
        }

    }

    GameBoard{
    id: _gameBoard
           anchors.fill: parent
           anchors.margins: 30
    }
    Text {
        id: name
        anchors.left: root.bottomLeft
        anchors.leftMargin: 5

        text: qsTr(" Step: ")+_gameBoard.internalSteps
    }

}
