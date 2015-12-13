#ifndef PARKING_H
#define PARKING_H

#include <QtQuick/qsgnode.h>
#include <QQuickItem>
#include <QVector>
#include <QVariantList>
#include <QBitArray>
#include "pplacesnode.h"
#include "plinesnode.h"
#include "place.h"
class AbstrAutoMarking;

class ParkingNode : public QSGNode
{
public:
    PLinesNode      *m_lines;
    PPlacesNode     *m_places;
    PPlacesNode     *m_roads;
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

    QList<Place *> places() const;
    QVector<Place *> placesList() const;
//    void setPlacesList(const QVector<Place*> &placesList);
    void pushPlaceInList(Place *place);
    void removePlace(int index);
    void clearPlaces();

    void transformVertexes(double angle);
    QPointF findCenter(QVector<QPointF> vertexes);

    QVector<Place *> roadsList() const;

    bool changePlacetype(int index, int type, bool isEntry = false);

    // TODO Улучшить подсчет вместимости
    // TODO Поверку на самопересечение

private:
    QVector<QPointF> m_vertexes;        // Массив вершин многоугольника
    int m_linesCount;                   // Число полос
    QSizeF m_place;                     // Квадрат описывающий парковочное место
    uint m_area;                        // Площадь парковки
    QList<Place *> m_places;          // Массив парковочных мест
    QBitArray  m_entryMask;
    // TODO Список внутренних препятствий
};

class ParkingQuickItem : public QQuickItem
{
    Q_OBJECT
public:
    ParkingQuickItem();
    Q_PROPERTY(int size READ getArea NOTIFY parkingChanged)

    Q_PROPERTY(int capacity READ getCapacity NOTIFY parkingChanged)

    Q_PROPERTY(QVariantList vertexes READ vertexes NOTIFY parkingChanged)

    Q_INVOKABLE void addVertex(double x, double y);                                 // Добавить вершину
    Q_INVOKABLE void changeVertex(double x, double y, uint index);                  // Изменить вершину
    Q_INVOKABLE void removeVertex(uint index);                                      // Удалить вершину
    Q_INVOKABLE int  getX(int index);                                               // Получить x координату вершины
    Q_INVOKABLE int  getY(int index);                                               // Получить y координату вершины
    Q_INVOKABLE void setParkingPlaceSize(uint width, uint height);                  // Установить размер парк. места
    Q_INVOKABLE void setParkingLinesCount(uint count);                              // Установить число полос
    Q_INVOKABLE QPointF checkNeighboring(double x, double y, int selectIndex);      // Проверка на близость к другой точке по X
    Q_INVOKABLE QVector3D findPointonLine(double x, double y);                         // Поиск точки на одной из сторон прямоугольника
    Q_INVOKABLE bool startMarking();                                                // Старт разметки парковки
    Q_INVOKABLE void addEntry(double x, double y, double w, double h, int index);
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
        res.reserve(m_parking.roadsList().count());
        for(auto i : m_parking.roadsList())
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
};

#endif // PARKING_H
