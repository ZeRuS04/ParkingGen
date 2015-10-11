#include "plinesnode.h"

PLinesNode::PLinesNode(float size, const QColor &color)
    : m_geometry(QSGGeometry::defaultAttributes_Point2D(), 0)
{
    setGeometry(&m_geometry);
    m_geometry.setLineWidth(size);
    m_geometry.setDrawingMode(GL_LINE_LOOP);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
}

void PLinesNode::updateGeometry(const QRectF &bounds, const QVector<QPointF> &points)
{

    int segmentsCount = points.size();
    if(segmentsCount == 0){
        m_geometry.allocate(1);
        QSGGeometry::Point2D *vertices = m_geometry.vertexDataAsPoint2D();
        vertices[0].set(0, 0);
        markDirty(QSGNode::DirtyGeometry);
    }
    if(segmentsCount > 0){
        m_geometry.allocate(segmentsCount);
        QSGGeometry::Point2D *vertices = m_geometry.vertexDataAsPoint2D();
        for (int i = 0; i < segmentsCount; ++i) {
            vertices[i].set(points.at(i).x(), points.at(i).y());
        }
        markDirty(QSGNode::DirtyGeometry);
    }
}

