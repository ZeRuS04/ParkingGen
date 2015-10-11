#ifndef PLINESNODE_H
#define PLINESNODE_H


#include <QSGGeometryNode>
#include <QtQuick/qsgflatcolormaterial.h>

/*
 *  Класс: геометрическое описание расположения стен парковки.
 */

class PLinesNode : public QSGGeometryNode
{
public:
    PLinesNode(float size, const QColor &color);


    void updateGeometry(const QRectF &bounds, const QVector<QPointF> &points);


private:
    QSGGeometry m_geometry;
};

#endif // PLINESNODE_H
