#include "circle.h"

Circle::Circle()
{

}

void Circle::paint(QPainter &painter)
{
    painter.drawEllipse(start.x(), start.y(),end.x() - start.x(), end.y() - start.y());
}
