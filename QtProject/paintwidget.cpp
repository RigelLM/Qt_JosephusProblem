#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
        : QWidget(parent), currShapeCode(Shape::Line), shape(NULL), perm(false)
{
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void PaintWidget::paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        //draw a white canvas
        painter.setBrush(Qt::white);
        painter.drawRect(0, 0, size().width(), size().height());
        //draw the past shapes as well
        foreach(Shape* shape, shapeList) {
                shape->paint(painter);
        }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if(candraw)
    {
        switch(currShapeCode)
        {
        case Shape::Line:
                {
                        shape = new Line;
                        break;
                }
        case Shape::Rect:
                {
                        shape = new Rect;
                        break;
                }
        case Shape::Circle:
                {
                        shape = new Circle;
                        break;
                }
        }
        //paint the current shape
        if(shape != NULL) {
                perm = false;
                shapeList<<shape;
                shape->setStart(event->pos());
                shape->setEnd(event->pos());
        }

    }
}
void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(candraw)
    {
        if(shape && !perm)
        {
                shape->setEnd(event->pos());
                update();
        }
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(candraw)
    {
        perm = true;
        //tell main window that the shapeList is updated
        emit PWReturn();
    }
}
