import QtQuick 2.0
import QtQuick.Controls 2.0

import "."

Item {
    id: root
    property string text

    anchors {
        bottom: parent.bottom
        horizontalCenter: parent.horizontalCenter
        margins: 24
    }

    property int hpadding: 24
    property int vpadding: 6
    width: label.width + 2 * hpadding
    height: label.height + 2 * vpadding

    Rectangle {
        id: background
        anchors.fill: parent
        radius: root.height / 2
        color: Style.toast.backgroundColor
        opacity: 0.6
    }

    Label {
        id: label
        x: root.hpadding
        y: root.vpadding
        text: root.text
        color: Style.toast.textColor
    }
}
