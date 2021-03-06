#ifndef PPLACESNODE_H
#define PPLACESNODE_H


#include <QSGGeometryNode>
#include <QtQuick/qsgflatcolormaterial.h>
#include "place.h"
/*
 *  Класс: геометрическое описание расположения парковочных мест.
 */

class PPlacesNode : public QSGGeometryNode
{
public:
    PPlacesNode(float size, const QColor &color);

    void updateGeometry(const QRectF &bounds, const QVector<Place *> &places);


private:
    QSGGeometry m_geometry;
};

#endif // PPLACESNODE_H
