#ifndef ABSTRAUTOMARKING_H
#define ABSTRAUTOMARKING_H

#include "parking.h"

#define OK                   0
#define PARKING_INIT_ERR    -100
#define UNKNOWN_ERR         -255

class AbstrAutoMarking
{
public:
    AbstrAutoMarking()
        : m_parking(NULL)
    {}

    int start(Parking *parking){
        m_parking = parking;
        if(m_parking == NULL)
            return PARKING_INIT_ERR;
        return algorithm();
    }

    virtual int algorithm() = 0;

protected:
    Parking* m_parking;
};

#endif // ABSTRAUTOMARKING_H
