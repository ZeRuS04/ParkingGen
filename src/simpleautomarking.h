#ifndef SIMPLEAUTOMARKING_H
#define SIMPLEAUTOMARKING_H

#include <QVector>
#include "abstrautomarking.h"

class SimpleAutoMarking : public AbstrAutoMarking
{
public:
    SimpleAutoMarking();

    int algorithm();

    int getAllPoints();
    void getSimpleRect();
    int initialGrid();

    void transformParking();
    void fillPlaces();

private:
    QVector<double> m_ox;
    QVector<double> m_oy;

    int m_simpleRectSize;

    bool **m_grid;
    double m_length;
    int m_gridHeight;
    int m_gridWidth;
};

#endif // SIMPLEAUTOMARKING_H
