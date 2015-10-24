#include <QPolygonF>
#include "simpleautomarking.h"
#include "parkingplace.h"
#include <qmath.h>

SimpleAutoMarking::SimpleAutoMarking()
  : m_gridWidth(0)
  , m_gridHeight(0)
  , m_length(0)
{}

int SimpleAutoMarking::algorithm()
{
    int rcod = OK;
    transformParking();
    rcod = initialGrid();
    fillPlaces();
    return rcod;
}

int SimpleAutoMarking::getAllPoints()
{
    foreach (QPointF point, m_parking->vertexes()) {
        m_ox << point.x();
        m_oy << point.y();
    }

    if(m_ox.isEmpty() || m_oy.isEmpty())
        return PARKING_INIT_ERR;

    qSort(m_ox.begin(), m_ox.end());
    qSort(m_oy.begin(), m_oy.end());

    return OK;
}

void SimpleAutoMarking::getSimpleRect()
{
    if(m_parking->place().width() < m_parking->place().height())
        m_simpleRectSize = m_parking->place().width();
    else
        m_simpleRectSize = m_parking->place().height();

}

int SimpleAutoMarking::initialGrid()
{
    int rcod = OK;
    rcod = getAllPoints();

    if(rcod != OK)
        return rcod;

    int dx = m_ox.last() - m_ox.first();
    int dy = m_oy.last() - m_oy.first();
    m_length = m_parking->place().width() >= m_parking->place().height() ? m_parking->place().width()
                                                                         : m_parking->place().height();
    m_gridWidth = dx / m_length + 1;
    m_gridHeight = dy / m_length + 1;

    if(m_length <= 0 || dx == 0 || dy == 0)
        return PARKING_INIT_ERR;

    QPolygonF polygon(m_parking->vertexes());
    m_grid = new bool*[m_gridWidth];
    for(int j = 0; j < (m_gridWidth); j++){
        m_grid[j] = new bool[m_gridHeight];
        for( int i = 0; i < (m_gridHeight); i++ ){
            m_grid[j][i] = polygon.containsPoint(QPointF(m_ox.first() + j * m_length, m_oy.first() + i * m_length), Qt::WindingFill);
        }
    }
    return rcod;
}

void SimpleAutoMarking::transformParking()
{
    QMap<double, double> angles;
    QPointF oldVertex = m_parking->vertexes().last();
    foreach(QPointF vertex, m_parking->vertexes()){
        double dx = vertex.x() - oldVertex.x();
        double dy = vertex.y() - oldVertex.y();
        double alpha = qAtan2(dy, dx);
        alpha = fmod(alpha,M_PI/2);

        if(angles.contains(alpha)) {
            angles[alpha] += sqrt(dx*dx+dy*dy);
        } else {
            angles.insert(alpha, sqrt(dx*dx+dy*dy));
        }

        oldVertex = vertex;
    }
    double currentKey = 0;
    double currentValue = 0;

    QMap<double, double>::const_iterator i = angles.constBegin();
    while (i != angles.constEnd()) {
        if(i.value() > currentValue){
            currentKey = i.key();
            currentValue = i.value();
        }
        ++i;
    }
    m_parking->transformVertexes(-currentKey);
}

void SimpleAutoMarking::fillPlaces()
{
    for(int i = 1; i < m_gridWidth; ++i) {
        for( int j = 1; j < m_gridHeight; j++ ){
            if(m_grid[i-1][j-1] && m_grid[i][j-1] && m_grid[i-1][j] && m_grid[i][j])
            {
                m_parking->pushPlaceInList(new ParkingPlace(QRectF(QPointF(m_ox.first() + (i-1) * m_length, m_oy.first() + (j-1) * m_length), QSize(m_length, m_length))));
            }
        }
    }
}




