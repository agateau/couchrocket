import QtQuick 2.0

pragma Singleton

QtObject {
    property QtObject main: QtObject {
        property color backgroundColor: "black"
        property color textColor: "white"
        property int textSize: 24

        property color selectedColor: "#308cc6"
    }
}
