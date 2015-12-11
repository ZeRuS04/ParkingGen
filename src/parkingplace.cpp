#include "parkingplace.h"

ParkingPlace::ParkingPlace(QRectF rect)
    : Place(rect, TYPE_PARKINGPLACE)
{}

QVector<Place *> ParkingPlace::roads() const
{
    return m_roads;
}

void ParkingPlace::pushRoad(Place *road)
{
    m_roads << road;
}

void ParkingPlace::setRoads(const QVector<Place *> &roads)
{
    m_roads = roads;
}

