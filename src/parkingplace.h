#ifndef PARKINGPLACE_H
#define PARKINGPLACE_H

#include <QVector>

#include "place.h"

class Place : public Place
{
public:
    Place(QRectF rect);

    QVector<Place *> roads() const;
    void pushRoad(Place *road);
    void setRoads(const QVector<Place *> &roads);

private:
    QVector<Place*> m_roads;
};

#endif // PARKINGPLACE_H
