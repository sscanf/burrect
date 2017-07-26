import QtQuick 2.6
import QtQuick.Window 2.2
import com.zitro.zone.qmlcomponents 1.0

Window {
    visible: true
    width  : 340
    height : 480
    title  : qsTr("Hello World")

    Image {
        id: image
        anchors.fill: parent
        source: "oscar.jpg"

    }

    Blur {
        id    : blur
        x     : 32
        y     : 119
        width : 185
        height: 216
        z     : 10

        Text {
            anchors.centerIn: parent
            color: "white"
            text: qsTr("Drag Me!")
            font.pixelSize: 12
        }

        MouseArea{
            id: dragArea
            anchors.fill: parent
            drag.target : parent
        }
    }
}
