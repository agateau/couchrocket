import QtQuick 2.0

pragma Singleton

QtObject {
    property QtObject main: QtObject {
        property color backgroundColor: "black"
        property color textColor: "white"
        property int textSize: 24

        property color accentColor: "#308cc6"
    }

    property QtObject grid: QtObject {
        property int iconSize: 256
        property int hpadding: 12
        property int vpadding: 24
        property int labelPadding: 8
        property color labelBackgroundColor: "#222"
        property color imageBackgroundColor: "#444"
        property real selectedScale: 1.1
    }

    property QtObject toast: QtObject {
        property color backgroundColor: "gray"
        property color textColor: "white"
    }
}
