#include <ctime>
#include <qmath.h>

#include "parking.h"
#include "abstrautomarking.h"
#include "simpleautomarking.h"
/***********************************
 *         ParkingQuickItem:
 ***********************************/
ParkingQuickItem::ParkingQuickItem()
    : m_geometryChanged(false)
    , m_parkingChanged(false)
    , m_markingAlg(NULL)
{
    m_markingAlg = new SimpleAutoMarking();
    setFlag(ItemHasContents, true);
}

void ParkingQuickItem::addVertex(double x, double y)
{
    m_parkingChanged = true;
    m_parking.addVertex(x,y);
    update();
}

void ParkingQuickItem::changeVertex(double x, double y, uint index)
{
    m_parkingChanged = true;
    m_parking.changeVertex(x,y,index);
    update();
}

void ParkingQuickItem::removeVertex(uint index)
{
    m_parkingChanged = true;
    m_parking.removeVertex(index);
    update();
}

int ParkingQuickItem::getX(int index)
{
    return m_parking.getX(index);
}

int ParkingQuickItem::getY(int index)
{
    return m_parking.getY(index);
}

void ParkingQuickItem::setParkingPlaceSize(uint width, uint height)
{
    m_parkingChanged = true;
    m_parking.setPlace(QSizeF(width, height));
    update();
}

void ParkingQuickItem::setParkingLinesCount(uint count)
{
    m_parkingChanged = true;
    m_parking.setLinesCount(count);
    update();
}

QPointF ParkingQuickItem::checkNeighboring(double x, double y, int selectIndex)
{
    QPointF retPoint(x,y);
    for(int i = 0; i < m_parking.vertexes().size(); i++){
        if(i == selectIndex)
            continue;
        QPointF vertex =  m_parking.vertexes().at(i);
        if(abs(vertex.x()-x) < 20){
            retPoint.setX(vertex.x());
        }
        if(abs(vertex.y()-y) < 20){
            retPoint.setY(vertex.y());
        }
    }
    return retPoint;
}

QPointF ParkingQuickItem::findPointonLine(double x, double y)
{
    QPointF point(x,y);

//    if(m_parking.vertexes().isEmpty())
//        return point;
//    QList<int> list;
//    QPointF lastPoint(m_parking.vertexes().last());

//    // Ищем подходящие стороны многоугольника
//    for(int i = 0; i < m_parking.vertexes().size(); i++){
//        QPointF curPoint = m_parking.vertexes().at(i);
//        if(((curPoint.x() <= x) && (x <= lastPoint.x())) || ((curPoint.x() >= x) && (x >= lastPoint.x())) ||
//           ((curPoint.y() <= y) && (y <= lastPoint.y())) || ((curPoint.y() >= y) && (y >= lastPoint.y()))){
//            list << i;
//        }
//        lastPoint = curPoint;
//    }
//    // проверяем среди подходящих на отсутствие пересечений
//    foreach(int i, list){
//        if(i != 0)
//            lastPoint = m_parking.vertexes().at(i-1);
//        else
//            lastPoint = m_parking.vertexes().last();
//        QPointF curPoint = m_parking.vertexes().at(i);
//    }

    return point;

}

bool ParkingQuickItem::startMarking()
{
    uint start = clock();
    if( m_markingAlg  == NULL) {
        qCritical("Marking algorithm was not initialized!");
        return false;
    }

    m_parking.clearPlaces();
    int retErr = m_markingAlg->start(&m_parking);
    uint end = clock();
    qCritical("Marking algorithm finished. Time: %d msec. Return %d!", end - start, retErr);
    m_parkingChanged = true;
    m_geometryChanged = true;
    update();
    return retErr;

}

void ParkingQuickItem::addEntry(double x, double y, int angle)
{
    QRectF entry, exit;
    int width = m_parking.place().width();
    switch(angle % 360) {
    case 0:
        exit = QRectF(x - width, y - width/2, width, width);
        entry = QRectF(x, y - width/2, width, width);
        break;
    case 90:
        exit = QRectF(x - width/2, y, width, width);
        entry = QRectF(x - width/2, y - width, width, width);
        break;
    case 180:
        entry = QRectF(x - width/2, y, width, width);
        exit = QRectF(x - width/2, y - width, width, width);
        break;
    case 270:
        entry = QRectF(x - width/2, y, width, width);
        exit = QRectF(x - width/2, y - width, width, width);
        break;
    }

    Place *rEntry = new Place(entry, TYPE_ROAD);
    Place *rExit = new Place(exit, TYPE_ROAD);

    m_parking.pushRoadInList(rEntry);
    m_parking.pushRoadInList(rExit);

    emit parkingChanged();
}


QSGNode *ParkingQuickItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    ParkingNode *node= static_cast<ParkingNode *>(oldNode);

    QRectF bounds = boundingRect();

    if (!node) {
        node = new ParkingNode();
        node->m_places = new PPlacesNode(1, QColor("#ffff0000"));
        node->m_roads = new PPlacesNode(1, QColor("#ff0000ff"));
        node->m_lines = new PLinesNode(2, QColor("steelblue"));
        node->appendChildNode(node->m_lines);
        node->appendChildNode(node->m_places);
        node->appendChildNode(node->m_roads);

    }
    if (m_geometryChanged || m_parkingChanged) {
//        QVector<QPointF> *points = new QVector<QPointF>;
        node->m_lines->updateGeometry(bounds, m_parking.vertexes());
        node->m_places->updateGeometry(bounds, m_parking.placesList());
        node->m_roads->updateGeometry(bounds, m_parking.placesList());
        emit parkingChanged();
    }

    m_geometryChanged = false;
    m_parkingChanged = false;

    return node;
}

void ParkingQuickItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}



/***********************************
 *              Parking:
 ***********************************/

Parking::Parking()
    : m_linesCount(1)
    , m_place(QSizeF(0,0))
    , m_area(0)
{}

QVector<QPointF> Parking::vertexes() const
{
    return m_vertexes;
}

void Parking::setVertexes(const QVector<QPointF> &vertexes)
{
    m_vertexes = vertexes;
    setArea();
}

void Parking::addVertex(double x, double y)
{
    m_vertexes.append(QPointF(x,y));
    setArea();
}

void Parking::changeVertex(double x, double y, int index)
{
    if((index < 0) || (index >= m_vertexes.length()))
        return;
    // TODO WTF?!
    m_vertexes[index].setX(x);
    m_vertexes[index].setY(y);
    setArea();
}

void Parking::removeVertex(int index)
{
    if((index < 0) || (index >= m_vertexes.length()))
        return;
    m_vertexes.removeAt(index);
    setArea();
}

int Parking::getX(int index)
{
    if((index < 0) || (index >= m_vertexes.length()))
        return -100;
    return m_vertexes.at(index).x();
}

int Parking::getY(int index)
{
    if((index < 0) || (index >= m_vertexes.length()))
        return -100;
    return m_vertexes.at(index).y();
}

int Parking::linesCount() const
{
    return m_linesCount;
}

void Parking::setLinesCount(int linesCount)
{
    m_linesCount = linesCount;
}
QSizeF Parking::place() const
{
    return m_place;
}

void Parking::setPlace(const QSizeF &place)
{
    m_place = place;
}
uint Parking::capacity() const
{
    return m_area/(m_place.height()*m_place.width());
}

uint Parking::area() const
{
    return m_area;
}

void Parking::setArea()
{
    int s, res = 0;
    int n = m_vertexes.size();
    if(n < 3){
        m_area = 0;
        return;
    }

    // Расчет площади многоугольника через сумму площадей трапеций
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            s = m_vertexes.at(i).x()*(m_vertexes.at(n-1).y() - m_vertexes.at(i+1).y()); //если i == 0, то y[i-1] заменяем на y[n-1]
            res += s;
        }
        else
            if (i == n-1) {
                s = m_vertexes.at(i).x()*(m_vertexes.at(i-1).y() - m_vertexes.at(0).y()); // если i == n-1, то y[i+1] заменяем на y[0]
                res += s;
            }
            else {
                s = m_vertexes.at(i).x()*(m_vertexes.at(i-1).y() - m_vertexes.at(i+1).y());
                res += s;
            }
    }
    m_area = abs(res/2);
}
QVector<Place*> Parking::placesList() const
{
    return m_places;
}

void Parking::setPlacesList(const QVector<Place *> &placesList)
{
    m_places = placesList;
}

void Parking::pushPlaceInList(Place* place)
{
    m_places << place;

}

void Parking::clearPlaces()
{
    m_places.clear();
}

void Parking::transformVertexes(double angle)
{
    QPointF cPoint = findCenter(m_vertexes);
    for(int i = 0; i < m_vertexes.length(); i++) {
        m_vertexes[i].setX((m_vertexes[i].x()-cPoint.x()) * qCos(angle) - (m_vertexes[i].y() - cPoint.y()) * qSin(angle) + cPoint.x());
        m_vertexes[i].setY((m_vertexes[i].x()-cPoint.x()) * qSin(angle) + (m_vertexes[i].y() - cPoint.y()) * qCos(angle) + cPoint.y());
    }
}

QPointF Parking::findCenter(QVector<QPointF> vertexes)
{
    QVector<double> ox;
    QVector<double> oy;

    foreach (QPointF point, vertexes) {
        ox << point.x();
        oy << point.y();
    }

    qSort(ox.begin(), ox.end());
    qSort(oy.begin(), oy.end());

    return QPointF(ox.last() - ox.first(), oy.last() - oy.first());
}
QVector<Place *> Parking::getRoads() const
{
    return m_roads;
}

void Parking::pushRoadInList(Place *road)
{
    m_roads << road;
}

void Parking::setRoads(const QVector<Place *> &roads)
{
    m_roads = roads;
}

void Parking::clearRoads()
{
    m_roads.clear();
}

void Parking::removeRoad(int index)
{
    if(index > 0 && index < m_roads.length());
        m_roads.remove(index);
}







