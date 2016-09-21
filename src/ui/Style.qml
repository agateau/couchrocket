import QtQuick 2.0

pragma Singleton

QtObject {
    property QtObject main: QtObject {
        property color backgroundColor: "black"
        property color textColor: "white"
        property int textSize: 24

        property color selectedColor: "#308cc6"
    }

    property QtObject grid: QtObject {
        property int iconSize: 256
        property int highlightSize: 12
        property int highlightRadius: 6
    }

    property QtObject toast: QtObject {
        property color backgroundColor: "gray"
        property color textColor: "white"
    }
}
