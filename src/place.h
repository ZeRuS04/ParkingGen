#ifndef ABSTRACTPLACE_H
#define ABSTRACTPLACE_H

#include <QRectF>
#include <QVector>
#include <QObject>

#define TYPE_UNDEFIND       0
#define TYPE_PARKINGPLACE   1
#define TYPE_ROAD           2


class Place : public QObject
{
    Q_OBJECT

public:
    Place(QRectF rect, int type, QObject *parent = 0);

    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(double width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged)

    char type() const;
    void setType(char type);

    double x() const;
    double y() const;
    double width() const;
    double height() const;

    QVector<Place *> neighbors() const;
    void clearNeighbors();
    Place *neighbor(int index) const;
    void setNeighbors(const QVector<Place *> &neighbors);
    void setNeighbor(Place *neighbor, int index);

public slots:
    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);

signals:
    void xChanged(double x);
    void yChanged(double y);
    void widthChanged(double width);
    void heightChanged(double height);

protected:
    int m_type;

    double m_x;
    double m_y;
    double m_width;
    double m_height;

private:
    QVector<Place*> m_neighbors;
};

#endif // ABSTRACTPLACE_H
