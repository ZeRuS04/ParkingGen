#ifndef PARKING_H
#define PARKING_H

#include <QtQuick/qsgnode.h>
#include <QQuickItem>
#include <QList>

#include "pplacesnode.h"
#include "plinesnode.h"
#include "pvertexesnode.h"

class ParkingNode : public QSGNode
{
public:
    PLinesNode *m_lines;
    PVertexesNode *m_vertexes;
    PPlacesNode *m_places;
};

class Parking
{

public:
    Parking();

    QList<QPointF> vertexes() const;
    void setVertexes(const QList<QPointF> &vertexes);
    void addVertex(double x, double y);                                 // Добавить вершину
    void changeVertex(double x, double y, uint index);                  // Изменить вершину
    void removeVertex(uint index);                                      // Удалить вершину

    int linesCount() const;
    void setLinesCount(int linesCount);

    QRect place() const;
    void setPlace(const QRect &place);

    uint capacity() const;
    void setCapacity(const uint &capacity);

    uint area() const;
    void setArea(const uint &area);

    QList<QRect> placesList() const;
    void setPlacesList(const QList<QRect> &placesList);

    // TODO Подсчет площади
    // TODO Подсчет вместимости

private:
    QList<QPointF> m_vertexes;      // Массив точек
    int m_linesCount;               // Число полос
    QRect m_place;                  // Квадрат описывающий парковочное место
    uint m_capacity;                // Максимальное количество парковочных мест
    uint m_area;                    // Площадь парковки
    QList<QRect> m_placesList;      // Массив парковочных мест
    // TODO Список входов/выходов с парковки
    // TODO Список внутренних препятствий
};

class ParkingQuickItem : public QQuickItem
{
    Q_OBJECT
public:
    ParkingQuickItem();

    Q_INVOKABLE void addVertex(double x, double y);                                 // Добавить вершину
    Q_INVOKABLE void changeVertex(double x, double y, uint index);                  // Изменить вершину
    Q_INVOKABLE void removeVertex(uint index);                                      // Удалить вершину

    Q_INVOKABLE void setParkingPlaceSize(uint width, uint height);                  // Установить размер парк. места
    Q_INVOKABLE void setParkingLinesCount(uint count);                              // установить число полос
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);              // Событие отрисовки нод
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);     // Событие изменения геометрии окна

signals:

public slots:


private:
    Parking m_parking;

    bool m_geometryChanged;
    bool m_parkingChanged;
};

#endif // PARKING_H
