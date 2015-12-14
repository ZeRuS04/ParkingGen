import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import CustomGeometry 1.0

ApplicationWindow {
    id: mainRect
    title: qsTr("ParkingGen")
    width: 640
    height: 480
    visible: true
    property real scaleCof: 1
    color: "white"

    Item {
        id: parkingFiel
        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: data.top
        Parking{
            id: parking
            anchors.fill: parent

            property int currentVertex: -1
            property int vertexCount: 0
            signal posChanged(var ind)

            MouseArea{
                id: parkingMA
                anchors.fill: parent;
                hoverEnabled: mode.currentIndex === 1
                onPressed: {
                    switch(mode.currentIndex){
                    case 0:
                        if(parking.currentVertex === -1) {
                            parking.addVertex(mouse.x, mouse.y);
                            parking.vertexCount++;
                            parking.currentVertex = parking.vertexCount-1;
                        }
                        break;
                    case 1:
                            parking.addEntry(entry.x, entry.y, entry.width, entry.height, entry.point.z)
                        break;
                    }
                }
                onPositionChanged: {
                    switch(mode.currentIndex){
                    case 0:
                        var point = parking.checkNeighboring(mouse.x,mouse.y, parking.currentVertex);
                        parking.changeVertex(point.x, point.y,  parking.currentVertex);
                        parking.posChanged(parking.currentVertex);
                        break;
                    }
                }
                onReleased:{
                    parking.currentVertex = -1;
                }
            }
        }
        Repeater{
            id: parkingVertecies
            model: parking.vertexes
            delegate: Rectangle{
                id: vertex
                property alias select: vertexMA.pressed
                property int i: index
                x: modelData.x - width/2
                y: modelData.y - height/2
                color: (index == 0) || (index == parking.vertexCount-1) ? "red" : "green"
                border.color: "black"
                border.width: select ? 1 : 0
                width: 10
                height: width
                radius: width/2

                MouseArea{
                    id: vertexMA
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onPressed: {
                        parking.currentVertex = parent.i;
                        mouse.accepted = false;
                    }
                }
            }
        }
        Repeater{
            id: parkingRoads
            model: parking.roads
            delegate:         Rectangle{
                x: modelData.x
                y: modelData.y
                width: placeWidth.value
                height: placeHeigh.value
                color: modelData.isBegin() ? "lightgreen"
                                           : (modelData.isEnd() ? "darkred"
                                                               : "skyblue")
            }
        }

        Rectangle{
            id:  entry
            property vector3d point: parking.findPointonLine(parkingMA.mouseX - width/2,parkingMA.mouseY - height/2)
            x: point.x
            y: point.y
            visible: mode.currentIndex === 1
            width: placeWidth.value < placeHeigh.value ? placeWidth.value * 2
                                                       : placeHeigh.value * 2
            height: width
            color: "blue"

            MouseArea {
                anchors.fill: parent
//                onWheel: {
//                    if (wheel.angleDelta.y > 0)
//                        parent.rotation += 90;
//                    else
//                        parent.rotation -= 90;
//                }
                onPressed: mouse.accepted = false
            }
        }

        Rectangle{
            width: placeWidth.value
            height: placeHeigh.value
            border.width: 1
            border.color: "red"
            color: "transparent"
        }
    }

    Item{
        id: data
        height: 100
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        anchors.margins: 30
        GridLayout{
            rows: 3
            columns: 2
            anchors.fill: parent
             Text{
                 Layout.fillHeight: true
                 Layout.fillWidth: true
                 text: "Parking size = " + parking.size;
                 verticalAlignment: Text.AlignVCenter
             }
             Text{
                 Layout.fillHeight: true
                 Layout.fillWidth: true
                 text: "Parking capacity = " + parking.capacity;
                 verticalAlignment: Text.AlignVCenter
             }
             Row{
                 Layout.fillHeight: true
                 Layout.columnSpan: 2
                 spacing: 20
                 Text{
//                     width: 100
                     text: "Parking place size: w=";
                 }
                 SpinBox{
                     id: placeWidth
                     width: 100
                     value: 10
                     minimumValue: 10
                     maximumValue: 10000
                     onValueChanged: parking.setParkingPlaceSize(placeWidth.value, placeHeigh.value)
                 }
                 Text{
                     text: " h=";
                 }
                 SpinBox{
                     id: placeHeigh
                     width: 100
                     value: 10
                     minimumValue: 10
                     maximumValue: 10000
                     onValueChanged: parking.setParkingPlaceSize(placeWidth.value, placeHeigh.value)
                 }
                 Text{
                     text: "Mode:";
                 }
                 ComboBox {
                     id: mode
                     width: 100
                     model: [ "Add Vertex", "Add exit" ]
                 }
                 Component.onCompleted: parking.setParkingPlaceSize(placeWidth.value, placeHeigh.value)
             }
             Button{
                text: "Start"

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 2

                onClicked: {
                    parking.startMarking();
                }
             }

        }

    }
}
