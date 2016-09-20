import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

import QtGamepad 1.0

import CouchRocket 1.0

import "."

ApplicationWindow {
    id: root

    title: "Couch Rocket"

    width: 800
    height: 600

    color: Style.main.backgroundColor
    font.pixelSize: Style.main.textSize

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
        id: main
        anchors.fill: parent
        GridView {
            id: launcherView
            model: launcherModel
            anchors.fill: parent
            focus: true
            cellWidth: 300
            cellHeight: cellWidth

            delegate: LauncherItem {
                Keys.onPressed: {
                    root.autoStartCountDown = -1;
                }
                onLaunchRequested: {
                    launcherModel.launch(model.index);
                }
            }

            highlight: Highlight {
            }
            highlightMoveDuration: 200

            KeyNavigation.down: powerButton
        }

        Label {
            id: countDownText
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            color: Style.main.textColor
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

        Button {
            id: powerButton
            KeyNavigation.up: launcherView

            anchors {
                bottom: main.bottom
                left: main.left
            }

            Image {
                source: "qrc:/images/power.svg"
                width: 32
                height: width
                anchors.centerIn: parent
            }
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

    Connections {
        target: GamepadManager
        onGamepadConnected: gamepad.deviceId = deviceId
    }

    Gamepad {
        id: gamepad
        deviceId: GamepadManager.connectedGamepads.length > 0 ? GamepadManager.connectedGamepads[0] : -1
    }

    GamepadKeyNavigation {
        id: gamepadKeyNavigation
        gamepad: gamepad
        active: true
        buttonAKey: Qt.Key_Return
        buttonBKey: Qt.Key_Return
        buttonXKey: Qt.Key_Return
        buttonYKey: Qt.Key_Return
        buttonL1Key: Qt.Key_Return
        buttonL2Key: Qt.Key_Return
        buttonL3Key: Qt.Key_Return
        buttonR1Key: Qt.Key_Return
        buttonR2Key: Qt.Key_Return
        buttonR3Key: Qt.Key_Return
    }
}

