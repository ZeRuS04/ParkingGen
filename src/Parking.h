#ifndef PARKING_H
#define PARKING_H

#include <QtQuick/qsgnode.h>
#include <QQuickItem>
#include <QVector>

#include "pplacesnode.h"
#include "plinesnode.h"
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

    QVector<QRectF> placesList() const;
    void setPlacesList(const QVector<QRectF> &placesList);
    void pushPlaceInList(QRectF place);
    void clearPlaces();


    // TODO Улучшить подсчет вместимости
    // TODO Поверку на самопересечение


private:
    QVector<QPointF> m_vertexes;      // Массив точек
    int m_linesCount;               // Число полос
    QSizeF m_place;                 // Квадрат описывающий парковочное место
    uint m_area;                    // Площадь парковки
    QVector<QRectF> m_placesList;     // Массив парковочных мест
    // TODO Список входов/выходов с парковки
    // TODO Список внутренних препятствий
};

class ParkingQuickItem : public QQuickItem
{
    Q_OBJECT
public:
    ParkingQuickItem();
    Q_PROPERTY(int size READ getArea NOTIFY parkingChanged)

    Q_PROPERTY(int capacity READ getCapacity NOTIFY parkingChanged)

    Q_INVOKABLE void addVertex(double x, double y);                                 // Добавить вершину
    Q_INVOKABLE void changeVertex(double x, double y, uint index);                  // Изменить вершину
    Q_INVOKABLE void removeVertex(uint index);                                      // Удалить вершину
    Q_INVOKABLE int  getX(int index);                                               // Получить x координату вершины
    Q_INVOKABLE int  getY(int index);                                               // Получить y координату вершины
    Q_INVOKABLE void setParkingPlaceSize(uint width, uint height);                  // Установить размер парк. места
    Q_INVOKABLE void setParkingLinesCount(uint count);                              // Установить число полос
    Q_INVOKABLE QPointF checkNeighboring(int x, int y, int selectIndex);            // Проверка на близость к другой точке по X
    Q_INVOKABLE bool startMarking();                                                // Старт разметки парковки

    int getArea() const
    {
        return m_parking.area();
    }

    int getCapacity() const
    {
        return m_parking.capacity();
    }

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);              // Событие отрисовки нод
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);     // Событие изменения геометрии окна

signals:

    void parkingChanged();

public slots:


private:
    Parking m_parking;
    AbstrAutoMarking *m_markingAlg;
    bool m_geometryChanged;
    bool m_parkingChanged;
};

#endif // PARKING_H
