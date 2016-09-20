import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import CouchRocket 1.0

import "."

ItemDelegate {
    signal launchRequested

    property int margin: 12

    width: column.width + 2 * margin
    height: column.height + 2 * margin

    ColumnLayout {
        id: column
        x: margin
        y: margin
        Image {
            width: 256
            height: width
            sourceSize.width: width
            sourceSize.height: width
            source: model.decoration
            Layout.alignment: Qt.AlignHCenter
        }
        Label {
            text: model.display
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
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
