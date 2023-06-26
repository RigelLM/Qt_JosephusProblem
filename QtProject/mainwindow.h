#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QActionGroup>
#include <QSplitter>
#include "shape.h"
#include "paintwidget.h"
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void changeCurrentShape(Shape::Code newShape);
    void startdequeue();
    void dequeue(int n);

private slots:
        void drawLineActionTriggered();
        void drawRectActionTriggered();
        void drawCircleActionTriggered();
        void StartDequeueActionTriggered();
        void DequeueActionTriggered();
        void updateItems();
        void ChangeStride(int);

private:
    Ui::MainWindow *ui;
    PaintWidget* paintWidget;
    QListWidget* itemWidget;
    QSplitter* splitter;
    uint32_t stride = 1;
};
#endif // MAINWINDOW_H
