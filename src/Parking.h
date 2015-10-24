#ifndef PARKING_H
#define PARKING_H

#include <QtQuick/qsgnode.h>
#include <QQuickItem>
#include <QVector>
#include <QVariantList>

#include "pplacesnode.h"
#include "plinesnode.h"
#include "roadplace.h"
class AbstrAutoMarking;

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

    QVector<QPointF> vertexes() const;
    void setVertexes(const QVector<QPointF> &vertexes);
    void addVertex(double x, double y);                                 // Добавить вершину
    void changeVertex(double x, double y, int index);                   // Изменить вершину
    void removeVertex(int index);                                       // Удалить вершину
    int  getX(int index);                                               // Получить x координату вершины
    int  getY(int index);                                               // Получить y координату вершины

    int linesCount() const;
    void setLinesCount(int linesCount);

    QSizeF place() const;
    void setPlace(const QSizeF &place);

    uint capacity() const;                                              // Максимальное количество парковочных мест

    uint area() const;
    void setArea();

    QVector<ParkingPlace *> placesList() const;
    void setPlacesList(const QVector<ParkingPlace*> &placesList);
    void pushPlaceInList(ParkingPlace *place);
    void clearPlaces();

    void transformVertexes(double angle);
    QPointF findCenter(QVector<QPointF> vertexes);

    QVector<RoadPlace *> getRoads() const;
    void pushRoadInList(RoadPlace *road);
    void setRoads(const QVector<RoadPlace *> &roads);
    void clearRoads();
    void removeRoad(int index);


    // TODO Улучшить подсчет вместимости
    // TODO Поверку на самопересечение

private:
    QVector<QPointF> m_vertexes;        // Массив вершин многоугольника
    int m_linesCount;                   // Число полос
    QSizeF m_place;                     // Квадрат описывающий парковочное место
    uint m_area;                        // Площадь парковки
    QVector<ParkingPlace *> m_placesList;     // Массив парковочных мест
    QVector<RoadPlace *> m_roads;       // Список входов/выходов с парковки
    // TODO Список внутренних препятствий
};

class ParkingQuickItem : public QQuickItem
{
    Q_OBJECT
public:
    ParkingQuickItem();
    Q_PROPERTY(int size READ getArea NOTIFY parkingChanged)

    Q_PROPERTY(int capacity READ getCapacity NOTIFY parkingChanged)

    Q_PROPERTY(QList<QObject*> roads READ roads NOTIFY parkingChanged)

    Q_PROPERTY(QVariantList vertexes READ vertexes NOTIFY parkingChanged)

    Q_INVOKABLE void addVertex(double x, double y);                                 // Добавить вершину
    Q_INVOKABLE void changeVertex(double x, double y, uint index);                  // Изменить вершину
    Q_INVOKABLE void removeVertex(uint index);                                      // Удалить вершину
    Q_INVOKABLE int  getX(int index);                                               // Получить x координату вершины
    Q_INVOKABLE int  getY(int index);                                               // Получить y координату вершины
    Q_INVOKABLE void setParkingPlaceSize(uint width, uint height);                  // Установить размер парк. места
    Q_INVOKABLE void setParkingLinesCount(uint count);                              // Установить число полос
    Q_INVOKABLE QPointF checkNeighboring(double x, double y, int selectIndex);      // Проверка на близость к другой точке по X
    Q_INVOKABLE QPointF findPointonLine(double x, double y);                         // Поиск точки на одной из сторон прямоугольника
    Q_INVOKABLE bool startMarking();                                                // Старт разметки парковки
    Q_INVOKABLE void addEntry(double x, double y, int angle);
    int getArea() const
    {
        return m_parking.area();
    }

    int getCapacity() const
    {
        return m_parking.capacity();
    }

    QVariantList vertexes() const
    {
        QVariantList list;
        foreach(QPointF point, m_parking.vertexes()){
            list << QVariant(point);
        }
        return list;
    }

    QList<QObject*> roads() const
    {
        QList<QObject *> res;
        res.reserve(m_parking.getRoads().count());
        for(auto i : m_parking.getRoads())
            res.append(i);

        return res;
    }

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);              // Событие отрисовки нод
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);     // Событие изменения геометрии окна

signals:

    void parkingChanged();

private:
    Parking m_parking;
    AbstrAutoMarking *m_markingAlg;
    bool m_parkingChanged;
    bool m_geometryChanged;
    QVariantList m_roads;
};

#endif // PARKING_H
