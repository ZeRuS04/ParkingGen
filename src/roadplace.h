#ifndef ROADPLACE_H
#define ROADPLACE_H

#include "parkingplace.h"
#include <QObject>
#include <QList>

class RoadPlace : public Place
{
    Q_OBJECT
public:
    RoadPlace(QRectF rect);

    void setIsEnd(bool isEnd);
    void setIsBegin(bool isBegin);

    QList<Place *> parkingPlaces() const;
    void setParkingPlaces(const QList<Place *> &parkingPlaces);

    QList<RoadPlace *> roads() const;
    void setRoads(const QList<RoadPlace *> &roads);

public slots:
    bool isEnd() const;
    bool isBegin() const;

private:
    QList<Place *> m_parkingPlaces;
    QList<RoadPlace*> m_roads;

    bool m_isEnd;
    bool m_isBegin;

};

#endif // ROADPLACE_H
