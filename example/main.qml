import QtQuick 2.6
import QtQuick.Window 2.2
import com.zitro.zone.qmlcomponents 1.0

Window {
    visible: true
    width  : 640
    height : 480
    title  : qsTr("Hello World")

    Rectangle {
        color : "blue"
        anchors.fill: parent

        Text {
            id: text1
            x: 98
            y: 39
            width: 73
            height: 41
            color: "#ffffff"
            text: qsTr("Text")
            font.bold: true
            font.pixelSize: 30
        }

        Image {
            id: image
            anchors.fill: parent
            source: "oscar.jpg"
        }

    }

    Blur {
        id    : blur
        x     : 32
        y     : 119
        width : 185
        height: 216
        z     : 10

        MouseArea{
            id: dragArea
            anchors.fill: parent
            drag.target : parent
        }

        Component.onCompleted: {
           blur.screenShot();
        }
    }

}
