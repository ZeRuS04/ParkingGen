#include "abstractplace.h"

AbstractPlace::AbstractPlace(QRectF rect, char type, QObject *parent)
    : QObject(parent)
    , m_type(type)
    , m_x(rect.x())
    , m_y(rect.y())
    , m_width(rect.width())
    , m_height(rect.height())
{

}
char AbstractPlace::type() const
{
    return m_type;
}

void AbstractPlace::setType(char type)
{
    m_type = type;
}

double AbstractPlace::x() const
{
    return m_x;
}

double AbstractPlace::y() const
{
    return m_y;
}

double AbstractPlace::width() const
{
    return m_width;
}

double AbstractPlace::height() const
{
    return m_height;
}

void AbstractPlace::setX(double x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(x);
}

void AbstractPlace::setY(double y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(y);
}

void AbstractPlace::setWidth(double width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged(width);
}

void AbstractPlace::setHeight(double height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged(height);
}


