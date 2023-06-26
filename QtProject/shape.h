#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>
class Shape
{
public:

        enum Code {
                Line,
                Rect,
                Circle
        };

        Shape();

        ~Shape();

        void setStart(QPoint s)
        {
                start = s;
        }

        void setEnd(QPoint e)
        {
                end = e;
        }

        QPoint startPoint()
        {
                return start;
        }

        QPoint endPoint()
        {
                return end;
        }

        virtual void paint(QPainter & painter) = 0;

        //keep track of total amount of shapes/geometries
        static int count;

        int GetNum() { return num; }

protected:
        //serial number
        int num;
        QPoint start;
        QPoint end;
};
#endif // SHAPE_H
