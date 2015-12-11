#include "place.h"

Place::Place(QRectF rect, int type, QObject *parent)
    : QObject(parent)
    , m_type(type)
    , m_x(rect.x())
    , m_y(rect.y())
    , m_width(rect.width())
    , m_height(rect.height())
{
    m_neighbors.resize(4);
    for (int i = 0; i < m_neighbors.size(); ++i) {
        m_neighbors[i] = NULL;
    }
}
char Place::type() const
{
    return m_type;
}

void Place::setType(char type)
{
    m_type = type;
}

double Place::x() const
{
    return m_x;
}

double Place::y() const
{
    return m_y;
}

double Place::width() const
{
    return m_width;
}

double Place::height() const
{
    return m_height;
}

void Place::setX(double x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(x);
}

void Place::setY(double y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(y);
}

void Place::setWidth(double width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged(width);
}

void Place::setHeight(double height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged(height);
}

QVector<Place *> Place::neighbors() const
{
    return m_neighbors;
}

void Place::clearNeighbors()
{
    m_neighbors.clear();
    m_neighbors.resize(4);
    for (int i = 0; i < m_neighbors.size(); ++i) {
        m_neighbors[i] = NULL;
    }
}

Place *Place::neighbor(int index) const
{
    if (index < 0 || index >= m_neighbors.size())
        return NULL;
    return m_neighbors.at(index);
}

void Place::setNeighbors(const QVector<Place *> &neighbors)
{
    m_neighbors = neighbors;
}

void Place::setNeighbor(Place *neighbor, int index)
{
    if (index < 0 || index >= m_neighbors.size())
        return;
    m_neighbors[index] = neighbor;
}


