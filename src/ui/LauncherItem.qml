import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import CouchRocket 1.0

import "."

ItemDelegate {
    id: root
    signal launchRequested

    property bool isCurrentItem: GridView.isCurrentItem

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight

    function aboutToLaunch() {
        var feedback = launchFeedback.createObject(GridView.view);
        var coord = GridView.view.mapFromItem(image, 0, 0);
        feedback.x = coord.x;
        feedback.y = coord.y;
    }

    Behavior on scale {
        NumberAnimation {
            duration: 200
            easing.type: Easing.OutCubic
        }
    }

    states: [
        State {
            when: isCurrentItem
            PropertyChanges {
                target: root
                scale: Style.grid.selectedScale
            }
            PropertyChanges {
                target: labelBackground
                color: Style.main.accentColor
            }
        }

    ]

    Rectangle {
        id: imageBackground
        anchors {
            top: parent.top
            topMargin: Style.grid.innerMargin
            horizontalCenter: parent.horizontalCenter
        }
        color: Style.grid.imageBackgroundColor
        Behavior on color {
            ColorAnimation {
                duration: 200
            }
        }

        width: Style.grid.iconSize
        height: Style.grid.iconSize
        Image {
            id: image
            anchors.fill: parent

            sourceSize.width: width
            sourceSize.height: width
            source: model.decoration
        }
    }

    Rectangle {
        id: labelBackground
        anchors {
            top: imageBackground.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: imageBackground.width
        height: label.implicitHeight + 2 * Style.grid.labelPadding

        color: Style.grid.labelBackgroundColor

        Behavior on color {
            ColorAnimation {
                duration: 200
            }
        }

        Label {
            id: label
            anchors {
                fill: parent
                margins: Style.grid.labelPadding
            }
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
