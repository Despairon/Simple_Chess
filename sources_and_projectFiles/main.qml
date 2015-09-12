import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    title: qsTr("Simple chess")
    width: 480
    height: 480
    minimumWidth: 480
    minimumHeight: 480
    maximumWidth: 480
    maximumHeight: 480
    visible: true

    property alias chessBoard : gridView1
    property alias chessPieces : gridView2


    menuBar: MenuBar {
        objectName: "Menubar"
        Menu {
            title: qsTr("&Game")
            MenuItem {
                id: startMenuItem
                objectName: "startmenu"
                text: qsTr("&Start")
                onTriggered: {
                    if (!chessPieces.visible)
                        chessPieces.visible = true
                    stopMenuItem.enabled = true
                    saveMenuItem.enabled = true
                    startMenuItem.enabled = false
                    loadMenuItem.enabled = false
                    prevMenuItem.enabled = false
                    nextMenuItem.enabled = false
                }
            }
            MenuItem {
                id: loadMenuItem
                objectName: "loadmenu"
                text: qsTr("&Load")
                function rollBack(state) {
                    if (state == 1)
                    {
                        chessPieces.visible = false
                        startMenuItem.enabled = true
                        loadMenuItem.enabled = true
                        stopMenuItem.enabled = false
                        saveMenuItem.enabled = false
                        prevMenuItem.enabled = false
                        nextMenuItem.enabled = false
                    }
                    if (state == 3)
                    {
                        if (!chessPieces.visible)
                            chessPieces.visible = true;
                        prevMenuItem.enabled = true
                        nextMenuItem.enabled = true
                        startMenuItem.enabled = true
                        stopMenuItem.enabled = false
                        saveMenuItem.enabled = false
                    }
                }
                onTriggered: {
                    if (!chessPieces.visible)
                        chessPieces.visible = true;
                    prevMenuItem.enabled = true
                    nextMenuItem.enabled = true
                    startMenuItem.enabled = true
                    stopMenuItem.enabled = false
                    saveMenuItem.enabled = false
                }
            }
            MenuItem {
                id: stopMenuItem
                objectName: "stopmenu"
                text: qsTr("&Stop")
                enabled: false
                onTriggered: {
                    chessPieces.visible = false
                    startMenuItem.enabled = true
                    loadMenuItem.enabled = true
                    stopMenuItem.enabled = false
                    saveMenuItem.enabled = false
                }
            }
            MenuItem {
                id: saveMenuItem
                objectName: "savemenu"
                text: qsTr("&Save")
                enabled: false
            }
            MenuItem {
                text: qsTr("&Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("&History")
            MenuItem {
                id: nextMenuItem
                objectName: "nextMenu"
                text : qsTr("&Next Step")
                shortcut: "right"
                enabled: false
            }
            MenuItem {
                id: prevMenuItem
                objectName: "prevMenu"
                text : qsTr("&Previous Step")
                shortcut: "left"
                enabled: false
            }
        }
    }

    GridView {
        signal cellClicked(int indx)
        id: gridView1
        objectName: "ChessBoard"
        x: 140
        y: 60
        width: 360
        height: 360
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        contentWidth: 0
        flickableDirection: Flickable.AutoFlickDirection
        boundsBehavior: Flickable.StopAtBounds
        cacheBuffer: 0
        keyNavigationWraps: false
        snapMode: GridView.NoSnap
        layoutDirection: Qt.LeftToRight
        interactive: false
        flickDeceleration: 0
        maximumFlickVelocity: 0
        contentHeight: 0
        highlightRangeMode: GridView.NoHighlightRange
        flow: GridView.FlowLeftToRight
        model: ListModel {
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

            ListElement {
                colorCode: "#593a00"
            }
            ListElement {
                colorCode: "#cfae67"
            }

        }

        cellHeight: 45
        cellWidth: 45
        delegate: Item {
            x: 5
            height: 50
            Column {
                Rectangle {
                    width: 45
                    height: 45
                    color: colorCode
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            MouseArea{
                id: mousearea
                width: gridView1.cellWidth
                height: gridView1.cellHeight
                onClicked:
                {
                        gridView1.currentIndex = index
                        gridView1.cellClicked(index)
                }
            }
        }
        Rectangle {
                    id: highlight
                    color: "lightblue"
                    width:gridView1.cellWidth
                    height:gridView1.cellHeight
                    x: gridView1.currentItem.x
                    y: gridView1.currentItem.y
                    radius: 9
                    opacity: 0.85
                }

        Rectangle {
            id: rectangle1
            color: "#5a3717"
            border.color: "#000000"
            anchors.rightMargin: -25
            anchors.leftMargin: -25
            anchors.bottomMargin: -25
            anchors.topMargin: -25
            anchors.fill: parent
            z: -1
            border.width: 3

            Label {
                id: label1
                text: qsTr("     A             B            C             D            E              F              G           H")
                horizontalAlignment: Text.AlignLeft
                font.bold: true
                anchors.right: parent.right
                anchors.rightMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 25
                anchors.top: parent.top
                anchors.topMargin: 8
            }

            Label {
                id: label2
                x: -8
                y: -3
                text: qsTr("     A             B            C             D            E              F              G           H")
                horizontalAlignment: Text.AlignLeft
                anchors.leftMargin: 25
                anchors.top: parent.top
                anchors.topMargin: 389
                font.bold: true
                anchors.right: parent.right
                anchors.rightMargin: 25
                anchors.left: parent.left
            }

            Label {
                id: label3
                x: 8
                y: 27
                width: 16
                height: 356
                text: "\n8\n\n\n\n7\n\n\n6\n\n\n\n5\n\n\n4\n\n\n3\n\n\n\n2\n\n\n\n1"
                textFormat: Text.AutoText
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                font.bold: true
                wrapMode: Text.NoWrap
            }

            Label {
                id: label4
                x: 386
                y: 27
                width: 16
                height: 356
                text: "\n8\n\n\n\n7\n\n\n6\n\n\n\n5\n\n\n4\n\n\n3\n\n\n\n2\n\n\n\n1"
                horizontalAlignment: Text.AlignHCenter
                textFormat: Text.AutoText
                font.bold: true
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignTop
            }
        }
        Rectangle {
            id: rectangle2
            x: 0
            y: 0
            width: 360
            height: 360
            color: "#00000000"
            border.width: 3
            z: 0
        }
    }

    GridView {
        id: gridView2
        objectName: "ChessPieces"
        x: 140
        y: 60
        width: 360
        height: 360
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        boundsBehavior: Flickable.StopAtBounds
        cacheBuffer: 0
        cellHeight: 45
        highlightRangeMode: GridView.NoHighlightRange
        interactive: false
        contentWidth: 0
        cellWidth: 45
        snapMode: GridView.NoSnap
        keyNavigationWraps: false
        model: ListModel {
            objectName: "ListModel"
            ListElement {
                image: "chess/chess/bTower.png"
            }

            ListElement {
                image: "chess/chess/bHorse.png"
            }

            ListElement {
                image: "chess/chess/bBishop.png"
            }

            ListElement {
                image: "chess/chess/bQueen.png"
            }

            ListElement {
                image: "chess/chess/bKing.png"
            }

            ListElement {
                image: "chess/chess/bBishop.png"
            }

            ListElement {
                image: "chess/chess/bHorse.png"
            }

            ListElement {
                image: "chess/chess/bTower.png"
            }

            ListElement {
                image: "chess/chess/bPawn.png"
            }

            ListElement {
                image: "chess/chess/bPawn.png"
            }

            ListElement {
                image: "chess/chess/bPawn.png"
            }

            ListElement {
                image: "chess/chess/bPawn.png"
            }

            ListElement {
                image: "chess/chess/bPawn.png"
            }

            ListElement {
                image: "chess/chess/bPawn.png"
            }

            ListElement {
                image: "chess/chess/bPawn.png"
            }

            ListElement {
                image: "chess/chess/bPawn.png"
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {

            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {

            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
            }

            ListElement {
                image: "chess/chess/wPawn.png"
            }

            ListElement {
                image: "chess/chess/wPawn.png"
            }

            ListElement {
                image: "chess/chess/wPawn.png"
            }

            ListElement {
                image: "chess/chess/wPawn.png"
            }

            ListElement {
                image: "chess/chess/wPawn.png"
            }

            ListElement {
                image: "chess/chess/wPawn.png"
            }

            ListElement {
                image: "chess/chess/wPawn.png"
            }

            ListElement {
                image: "chess/chess/wPawn.png"
            }

            ListElement {
                image: "chess/chess/wTower.png"
            }

            ListElement {
                image: "chess/chess/wHorse.png"
            }

            ListElement {
                image: "chess/chess/wBishop.png"
            }

            ListElement {
                image: "chess/chess/wQueen.png"
            }

            ListElement {
                image: "chess/chess/wKing.png"
            }

            ListElement {
                image: "chess/chess/wBishop.png"
            }

            ListElement {
                image: "chess/chess/wHorse.png"
            }

            ListElement {
                image: "chess/chess/wTower.png"
            }
        }
        flow: GridView.FlowLeftToRight
        flickDeceleration: 0
        maximumFlickVelocity: 0
        layoutDirection: Qt.LeftToRight
        flickableDirection: Flickable.AutoFlickDirection
        contentHeight: 0
        delegate: Item {
            objectName: "delegate"
            x: 5
            height: 50
            Column {
                objectName: "column"
                Image {
                    objectName: "img"
                    source: image
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }

}
