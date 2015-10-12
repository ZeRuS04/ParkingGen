#include "pplacesnode.h"

PPlacesNode::PPlacesNode(float size, const QColor &color)
    : m_geometry(QSGGeometry::defaultAttributes_Point2D(), 0)
{
    setGeometry(&m_geometry);
    m_geometry.setLineWidth(size);
    m_geometry.setDrawingMode(GL_QUADS);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
}

void PPlacesNode::updateGeometry(const QRectF &bounds, const QVector<QRectF> &places)
{
    int segmentsCount = places.size()*4;
    if(segmentsCount > 0){
        m_geometry.allocate(segmentsCount);
        QSGGeometry::Point2D *vertices = m_geometry.vertexDataAsPoint2D();

        for (int i = 0; i < places.size(); ++i) {
            vertices[i*4].set(places.at(i).topLeft().x(), places.at(i).topLeft().y());
            vertices[i*4+1].set(places.at(i).topRight().x(), places.at(i).topRight().y());
            vertices[i*4+2].set(places.at(i).bottomRight().x(), places.at(i).bottomRight().y());
            vertices[i*4+3].set(places.at(i).bottomLeft().x(), places.at(i).bottomLeft().y());
        }
        markDirty(QSGNode::DirtyGeometry);
    }
}

