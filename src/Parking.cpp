#include "parking.h"

/***********************************
 *         ParkingQuickItem:
 ***********************************/
ParkingQuickItem::ParkingQuickItem()
{
    setFlag(ItemHasContents, true);
}

void ParkingQuickItem::addVertex(double x, double y)
{
    m_parkingChanged = true;
    m_parking.addVertex(x,y);
}

void ParkingQuickItem::changeVertex(double x, double y, uint index)
{
    m_parkingChanged = true;
    m_parking.changeVertex(x,y,index);
}

void ParkingQuickItem::removeVertex(uint index)
{
    m_parkingChanged = true;
    m_parking.removeVertex(index);
}

void ParkingQuickItem::setParkingPlaceSize(uint width, uint height)
{
    m_parkingChanged = true;
    m_parking.setPlace(QRectF(0,0,width, height));
}

void ParkingQuickItem::setParkingLinesCount(uint count)
{
    m_parkingChanged = true;
    m_parking.setLinesCount(count);
}

QSGNode *ParkingQuickItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    ParkingNode *node= static_cast<ParkingNode *>(oldNode);

    QRectF bounds = boundingRect();

    if (!node) {
        node = new ParkingNode();
        node->background = new  BackgroundNode(QColor(0, 0, 0, 30));
        node->line = new LineNode(2, QColor("steelblue"));
        node->appendChildNode(node->m_lines);
        node->appendChildNode(node->m_vertexes);
        node->appendChildNode(node->m_places);

    }
    if (m_geometryChanged || m_parkingChanged) {
//        QList<QPointF> *points = new QList<QPointF>;
        node->m_lines->updateGeometry(bounds, m_vertexes);
        node->m_vertexes->setGeometry(node->m_lines);
        node->m_places->updateGeometry(bounds, m_parkingPlaces);
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
    , m_place(QRectF(0,0,0,0))
    , m_capacity(0)
    , m_area(0)
{}

QList<QPointF> Parking::vertexes() const
{
    return m_vertexes;
}

void Parking::setVertexes(const QList<QPointF> &vertexes)
{
    m_vertexes = vertexes;
}

void Parking::addVertex(double x, double y)
{
    m_vertexes.append(QPointF(x,y));
}

void Parking::changeVertex(double x, double y, uint index)
{
    if((index < 0) || (index >= m_vertexes.length()))
        return;
    m_vertexes.at(index).setX(x);
    m_vertexes.at(index).setY(y);
}

void Parking::removeVertex(uint index)
{
    if((index < 0) || (index >= m_vertexes.length()))
        return;
    m_vertexes.removeAt(index);
}

int Parking::linesCount() const
{
    return m_linesCount;
}

void Parking::setLinesCount(int linesCount)
{
    m_linesCount = linesCount;
}
QRect Parking::place() const
{
    return m_place;
}

void Parking::setPlace(const QRect &place)
{
    m_place = place;
}
uint Parking::capacity() const
{
    return m_capacity;
}

void Parking::setCapacity(const uint &capacity)
{
    m_capacity = capacity;
}
uint Parking::area() const
{
    return m_area;
}

void Parking::setArea(const uint &area)
{
    m_area = area;
}
QList<QRect> Parking::placesList() const
{
    return m_placesList;
}

void Parking::setPlacesList(const QList<QRect> &placesList)
{
    m_placesList = placesList;
}






