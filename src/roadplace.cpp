#include "roadplace.h"

RoadPlace::RoadPlace(QRectF rect)
    : AbstractPlace(rect, TYPE_ROAD)
    , m_isEnd(false)
    , m_isBegin(false)
{}
bool RoadPlace::isEnd() const
{
    return m_isEnd;
}

void RoadPlace::setIsEnd(bool isEnd)
{
    m_isEnd = isEnd;
}
bool RoadPlace::isBegin() const
{
    return m_isBegin;
}

void RoadPlace::setIsBegin(bool isBegin)
{
    m_isBegin = isBegin;
}
QList<ParkingPlace *> RoadPlace::parkingPlaces() const
{
    return m_parkingPlaces;
}

void RoadPlace::setParkingPlaces(const QList<ParkingPlace *> &parkingPlaces)
{
    m_parkingPlaces = parkingPlaces;
}
QList<RoadPlace *> RoadPlace::roads() const
{
    return m_roads;
}

void RoadPlace::setRoads(const QList<RoadPlace *> &roads)
{
    m_roads = roads;
}





