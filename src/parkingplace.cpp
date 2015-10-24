#include "parkingplace.h"

ParkingPlace::ParkingPlace(QRectF rect)
    : AbstractPlace(rect, TYPE_PARKINGPLACE)
{}

QVector<AbstractPlace *> ParkingPlace::roads() const
{
    return m_roads;
}

void ParkingPlace::pushRoad(AbstractPlace *road)
{
    m_roads << road;
}

void ParkingPlace::setRoads(const QVector<AbstractPlace *> &roads)
{
    m_roads = roads;
}

