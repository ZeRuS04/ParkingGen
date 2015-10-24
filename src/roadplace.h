#ifndef ROADPLACE_H
#define ROADPLACE_H

#include "parkingplace.h"
#include <QObject>
#include <QList>

class RoadPlace : public AbstractPlace
{
    Q_OBJECT
public:
    RoadPlace(QRectF rect);

    void setIsEnd(bool isEnd);
    void setIsBegin(bool isBegin);

    QList<ParkingPlace *> parkingPlaces() const;
    void setParkingPlaces(const QList<ParkingPlace *> &parkingPlaces);

    QList<RoadPlace *> roads() const;
    void setRoads(const QList<RoadPlace *> &roads);

public slots:
    bool isEnd() const;
    bool isBegin() const;

private:
    QList<ParkingPlace *> m_parkingPlaces;
    QList<RoadPlace*> m_roads;

    bool m_isEnd;
    bool m_isBegin;

};

#endif // ROADPLACE_H
