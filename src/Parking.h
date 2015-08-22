#ifndef PARKING_H
#define PARKING_H

#include <QtQuick/qsgnode.h>
#include <QQuickItem>
#include <QList>

#include "pplacesnode.h"
#include "plinesnode.h"

class ParkingNode : public QSGNode
{
public:
    PLinesNode      *m_lines;
    PPlacesNode     *m_places;
};

class Parking
{

public:
    Parking();

    QList<QPointF> vertexes() const;
    void setVertexes(const QList<QPointF> &vertexes);
    void addVertex(double x, double y);                                 // Добавить вершину
    void changeVertex(double x, double y, int index);                   // Изменить вершину
    void removeVertex(int index);                                       // Удалить вершину
    int  getX(int index);                                               // Получить x координату вершины
    int  getY(int index);                                               // Получить y координату вершины

    int linesCount() const;
    void setLinesCount(int linesCount);

    QRectF place() const;
    void setPlace(const QRectF &place);

    uint capacity() const;
    void setCapacity(const uint &capacity);

    uint area() const;
    void setArea();

    QList<QRectF> placesList() const;
    void setPlacesList(const QList<QRectF> &placesList);

    // TODO Подсчет площади
    // TODO Подсчет вместимости
    // TODO Поверку на самопересечение

private:
    QList<QPointF> m_vertexes;      // Массив точек
    int m_linesCount;               // Число полос
    QRectF m_place;                 // Квадрат описывающий парковочное место
    uint m_capacity;                // Максимальное количество парковочных мест
    uint m_area;                    // Площадь парковки
    QList<QRectF> m_placesList;     // Массив парковочных мест
    // TODO Список входов/выходов с парковки
    // TODO Список внутренних препятствий
};

class ParkingQuickItem : public QQuickItem
{
    Q_OBJECT
public:
    ParkingQuickItem();
    Q_PROPERTY(int size READ getArea NOTIFY parkingChanged)


    Q_INVOKABLE void addVertex(double x, double y);                                 // Добавить вершину
    Q_INVOKABLE void changeVertex(double x, double y, uint index);                  // Изменить вершину
    Q_INVOKABLE void removeVertex(uint index);                                      // Удалить вершину
    Q_INVOKABLE int  getX(int index);                                               // Получить x координату вершины
    Q_INVOKABLE int  getY(int index);                                               // Получить y координату вершины
    Q_INVOKABLE void setParkingPlaceSize(uint width, uint height);                  // Установить размер парк. места
    Q_INVOKABLE void setParkingLinesCount(uint count);                              // Установить число полос
    Q_INVOKABLE QPointF checkNeighboring(int x, int y, int selectIndex);            // Проверка на близость к другой точке по X

    int getArea() const
    {
        return m_parking.area();
    }

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);              // Событие отрисовки нод
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);     // Событие изменения геометрии окна

signals:

    void parkingChanged();

public slots:


private:
    Parking m_parking;

    bool m_geometryChanged;
    bool m_parkingChanged;
};

#endif // PARKING_H
