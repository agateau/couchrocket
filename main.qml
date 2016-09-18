import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

import CouchRocket 1.0

Window {
    id: root

    title: "Couch Rocket"

    width: 800
    height: 600

    color: "black"

    property int autoStartCountDown: 5

    Component.onCompleted: {
        if (config.fullScreen) {
            showFullScreen();
        } else {
            show();
        }
    }

    LauncherModel {
        id: launcherModel
        path: config.launcherDir
    }

    Item {
        anchors.fill: parent
        ListView {
            id: launcherView
            model: launcherModel
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            height: 256
            focus: true
            orientation: Qt.Horizontal

            delegate: LauncherItem {
                Keys.onPressed: {
                    root.autoStartCountDown = -1;
                }
                onLaunchRequested: {
                    launcherModel.launch(model.index);
                }
            }

            highlight: Rectangle {
                color: "#308cc6"
                radius: 5
            }
            highlightMoveDuration: 200
        }

        Text {
            id: countDownText
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            color: "white"
            visible: false
            states: [
                State {
                    name: "countDown"
                    when: root.autoStartCountDown >= 0 && launcherView.count > 0
                    PropertyChanges {
                        target: countDownText
                        visible: true
                        text: qsTr("Starting %1 in %2...").arg(launcherModel.get(0).display).arg(root.autoStartCountDown)
                    }
                }
            ]
        }
    }

    Timer {
        interval: 1000
        repeat: root.autoStartCountDown > 0
        running: true
        onTriggered: {
            root.autoStartCountDown--;
            if (root.autoStartCountDown == 0) {
                launcherModel.launch(0);
            }
        }
    }
}

