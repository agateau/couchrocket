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
        property int hpadding: 36
        property int outerMargin: 2
        property int innerMargin: 4
        property int radius: 3
    }

    property QtObject toast: QtObject {
        property color backgroundColor: "gray"
        property color textColor: "white"
    }
}
