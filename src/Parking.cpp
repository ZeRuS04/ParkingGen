#include <ctime>

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

QPointF ParkingQuickItem::checkNeighboring(int x, int y, int selectIndex)
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
    update();
    return retErr;

}


QSGNode *ParkingQuickItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    ParkingNode *node= static_cast<ParkingNode *>(oldNode);

    QRectF bounds = boundingRect();

    if (!node) {
        node = new ParkingNode();
        node->m_places = new  PPlacesNode(2, QColor("green"));
        node->m_lines = new PLinesNode(2, QColor("steelblue"));
        node->appendChildNode(node->m_lines);
        node->appendChildNode(node->m_places);

    }
    if (m_geometryChanged || m_parkingChanged) {
//        QVector<QPointF> *points = new QVector<QPointF>;
        node->m_lines->updateGeometry(bounds, m_parking.vertexes());
        node->m_places->updateGeometry(bounds, m_parking.placesList());
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
QVector<QRectF> Parking::placesList() const
{
    return m_placesList;
}

void Parking::setPlacesList(const QVector<QRectF> &placesList)
{
    m_placesList = placesList;
}

void Parking::pushPlaceInList(QRectF place)
{
    m_placesList << place;

}

void Parking::clearPlaces()
{
    m_placesList.clear();
}






