#ifndef PPLACESNODE_H
#define PPLACESNODE_H


#include <QSGGeometryNode>

/*
 *  Класс: геометрическое описание расположения парковочных мест.
 */

class PPlacesNode : public QSGGeometryNode
{
public:
    PPlacesNode(float size, const QColor &color);

    void updateGeometry(const QRectF &bounds, const QList<QRectF> &places);


private:
    QSGGeometry m_geometry;
};

#endif // PPLACESNODE_H
