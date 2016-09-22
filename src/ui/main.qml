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

            width: cellWidth * columnCount

            property int columnCount: Math.floor(main.width / (Style.grid.iconSize + 2 * Style.grid.hpadding))

            cellWidth: Math.floor(main.width / columnCount)
            cellHeight: Style.grid.iconSize + 2 * (Style.grid.innerMargin + Style.grid.outerMargin) + 3 * Style.main.textSize

            delegate: LauncherItem {
                Keys.onPressed: {
                    root.autoStartCountDown = -1;
                }
                onLaunchRequested: {
                    launch();
                }
            }
        }

        ToastLabel {
            id: countDownToast
            visible: false
            states: [
                State {
                    name: "countDown"
                    when: root.autoStartCountDown >= 0 && launcherView.count > 0
                    PropertyChanges {
                        target: countDownToast
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
                launch();
            }
        }
    }

    function launch() {
        launcherView.currentItem.aboutToLaunch();
        launcherModel.launch(launcherView.currentIndex);
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

