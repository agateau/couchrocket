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

        Loader {
            active: config.wallpaper !== ""
            anchors.fill: parent
            sourceComponent: Component {
                Image {
                    source: config.wallpaper
                    fillMode: Image.PreserveAspectCrop
                    clip: true
                }
            }
        }

        GridView {
            id: launcherView
            model: launcherModel
            anchors {
                fill: parent
                topMargin: Style.grid.iconSize * (Style.grid.selectedScale - 1)
            }
            focus: true

            width: cellWidth * columnCount

            property int columnCount: Math.floor(main.width / (Style.grid.iconSize + 2 * Style.grid.hpadding))

            cellWidth: Math.floor(main.width / columnCount)
            cellHeight: Style.grid.iconSize + 3 * Style.main.textSize + 2 * Style.grid.vpadding

            delegate: LauncherItem {
                onLaunchRequested: {
                    launcherView.currentIndex = model.index;
                    launchCurrentItem();
                }
            }
        }
    }

    function launchCurrentItem() {
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

