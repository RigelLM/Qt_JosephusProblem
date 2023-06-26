#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include <QtGui>
#include <QDebug>
#include "shape.h"
#include "line.h"
#include "rect.h"
#include "circle.h"
#include <QWidget>

class PaintWidget : public QWidget
{
        Q_OBJECT

public:
        PaintWidget(QWidget *parent = 0);
        //expose the shapeList to other widget so that the geometry list could be updated
        QList<Shape*> shapeList;

signals:
        void PWReturn();

public slots:
        //update the painting tool
        void setCurrentShape(Shape::Code s)
        {
                if(s != currShapeCode) {
                        currShapeCode = s;
                }
        }

        //update flags that control painting and dequeue process
        void StopDrawing()
        {
            candraw = !candraw;
            candequeue = !candequeue;
            currentPos = 0;
        }

        //dequeue if the size of shapeList is not 1
        void Dequeue(int n)
        {
            if(candequeue&&shapeList.size()!=1)
            {
                currentPos = (currentPos + n - 1)%shapeList.size();
                shapeList.removeAt(currentPos);
                update();
                //tell mainwindow that the shapeList is updated
                emit PWReturn();
            }
        }

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

private:
        Shape::Code currShapeCode;
        Shape *shape;
        //if finish drawing
        bool perm;
        bool candraw = true;
        bool candequeue = false;
        //the current iteration position
        int currentPos = 0;
};
#endif // PAINTWIDGET_H
