#ifndef PARKINGPLACE_H
#define PARKINGPLACE_H

#include "abstractplace.h"

class ParkingPlace : public AbstractPlace
{
public:
    ParkingPlace(QRectF rect);
};

#endif // PARKINGPLACE_H
