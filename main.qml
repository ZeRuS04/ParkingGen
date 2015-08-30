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
//    ColumnLayout{
//        id: mainLayout
//        anchors.fill: parent;
//        ScrollView{
//            id: mainScrollArea;
//            anchors.fill: parent;
//            contentItem: Item{
//                id: parkingField
//                width: parent.width*scaleCof; height: parent.height*scaleCof;

//            }
//        }

//    }
    Item {
        id: parkingFiel
        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: data.top
        Parking{
            id: parking
            anchors.fill: parent


            property int vertexCount: 0
            signal posChanged(var ind);

            MouseArea{
                id: parkingMA
                anchors.fill: parent;
                onPressed: {
                    parking.addVertex(mouse.x, mouse.y);
                    parking.vertexCount++;
                }
                onPositionChanged: {
                    var point = parking.checkNeighboring(mouse.x,mouse.y, parking.vertexCount-1);
                    parking.changeVertex(point.x, point.y, parking.vertexCount-1);
                    parking.posChanged(parking.vertexCount-1);
                }

                onClicked:{


                }
            }
        }
        Repeater{
            id: parkingVertecies
            model: parking.vertexCount
            delegate: Rectangle{
                id: vertex
                property bool select: false
                property int i: index
                x: parking.getX(index)-width/2;            y: parking.getY(index)-height/2;
                color: (index == 0) || (index == parking.vertexCount-1) ? "red" : "green"
                border.color: "black"
                border.width: select ? 2 : 0
                width: 10 + (select ? 5 : 0)
                height: width
                radius: width/2

                onXChanged: {
                    if(vertexMA.drag.active){
                        var point = parking.checkNeighboring(x+width/2, y+height/2, i);
                        vertex.x = point.x - width/2;   vertex.y = point.y - height/2;
                        parking.changeVertex(point.x, point.y, i);
                    }
                }
                onYChanged: {
                    if(vertexMA.drag.active){
                        var point = parking.checkNeighboring(x+width/2, y+height/2, i)
                        vertex.x = point.x - width/2;   vertex.y = point.y - height/2;
                        parking.changeVertex(point.x, point.y, i)
                    }
                }

                MouseArea{
                    id: vertexMA
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onEntered: width+=5;
                    onExited: width-=5;
                    drag.target: vertex
                    onClicked: {
                        vertex.select != vertex.select;
                    }

                }
                Connections{
                    target: parking
                    onPosChanged: {
                        if(ind == vertex.i){
                            x = parking.getX(ind)-width/2;
                            y = parking.getY(ind)-height/2;
                        }
                    }
                }
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
                 Text{
//                     width: 100
                     text: "Parking place size: w=";
                     verticalAlignment: Text.AlignVCenter
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
                     verticalAlignment: Text.AlignVCenter
                 }
                 SpinBox{
                     id: placeHeigh
                     width: 100
                     value: 10
                     minimumValue: 10
                     maximumValue: 10000
                     onValueChanged: parking.setParkingPlaceSize(placeWidth.value, placeHeigh.value)
                 }
             }
        }

    }


}
