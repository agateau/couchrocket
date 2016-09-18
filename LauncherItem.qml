import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

import CouchRocket 1.0

Item {
    signal launchRequested

    width: column.width
    height: column.height
    ColumnLayout {
        id: column
        Image {
            width: 256
            height: width
            sourceSize.width: width
            sourceSize.height: width
            source: model.decoration
            Layout.alignment: Qt.AlignHCenter
        }
        Text {
            text: model.display
            wrapMode: Text.WordWrap
            Layout.alignment: Qt.AlignHCenter
            color: "white"
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
