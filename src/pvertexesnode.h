#ifndef PVERTEXESNODE_H
#define PVERTEXESNODE_H


#include <QSGGeometryNode>

/*
 *  Класс: геометрическое описание вершин многоугольника описывающих парковку.
 */

class PVertexesNode : public QSGGeometryNode
{
public:
    PVertexesNode(float size, const QColor &color);

    void updateGeometry(const QRectF &bounds, const QList<QPointF> &points);


private:
    QSGGeometry m_geometry;
};

#endif // PVERTEXESNODE_H
