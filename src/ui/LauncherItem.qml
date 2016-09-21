import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import CouchRocket 1.0

import "."

ItemDelegate {
    signal launchRequested

    property int margin: Style.grid.highlightSize
    property int iconSize: Style.grid.iconSize

    width: column.width + 2 * margin
    height: column.height + 2 * margin

    Column {
        id: column
        x: margin
        y: margin
        width: iconSize
        Image {
            width: iconSize
            sourceSize.width: iconSize
            sourceSize.height: iconSize
            source: model.decoration
        }
        Label {
            width: iconSize
            text: model.display
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
            horizontalAlignment: Qt.AlignHCenter
            color: Style.main.textColor
            maximumLineCount: 2
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            launchRequested();
        }
    }
    
    Keys.onReturnPressed: {
        launchRequested();
    }
    Keys.onSpacePressed: {
        launchRequested();
    }
}
