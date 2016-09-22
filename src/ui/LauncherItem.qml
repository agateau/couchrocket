import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import CouchRocket 1.0

import "."

ItemDelegate {
    id: root
    signal launchRequested

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight

    function aboutToLaunch() {
        var feedback = launchFeedback.createObject(GridView.view);
        var coord = GridView.view.mapFromItem(image, 0, 0);
        feedback.x = coord.x;
        feedback.y = coord.y;
    }

    Rectangle {
        color: root.GridView.isCurrentItem ? "#555" : "#222"
        anchors {
            fill: parent
            margins: Style.grid.outerMargin
        }
        radius: Style.grid.radius

        Behavior on color {
            ColorAnimation {
                duration: 200
            }
        }

    Image {
        id: image
        anchors {
            top: parent.top
            topMargin: Style.grid.innerMargin
            horizontalCenter: parent.horizontalCenter
        }

        width: Style.grid.iconSize
        sourceSize.width: width
        sourceSize.height: width
        source: model.decoration
    }

    Label {
        anchors {
            top: image.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width
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

    Component {
        id: launchFeedback
        Image {
            id: launchImage
            width: Style.grid.iconSize
            sourceSize.width: width
            sourceSize.height: width
            source: model.decoration

            SequentialAnimation {
                running: true
                ParallelAnimation {
                    NumberAnimation {
                        target: launchImage
                        property: "scale"
                        to: 5
                        duration: 200
                    }
                    NumberAnimation {
                        target: launchImage
                        property: "opacity"
                        to: 0
                        duration: 200
                    }
                }
                ScriptAction {
                    script: {
                        launchImage.destroy();
                    }
                }
            }
        }
    }
}
