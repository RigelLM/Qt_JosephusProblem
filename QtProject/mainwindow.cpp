#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QToolBar *bar = new QToolBar;   //create tool bar
    this->addToolBar(bar);          //add the tool bar to the main window

    QActionGroup *group = new QActionGroup(bar);   //create action group

    QAction *drawLineAction = new QAction("Line", bar);
    drawLineAction->setIcon(QIcon(":/picture/line.png"));   //set the icon
    drawLineAction->setToolTip(tr("Draw a line.")); //set the notification text
    drawLineAction->setStatusTip(tr("Draw a line."));//set the status text
    drawLineAction->setCheckable(true);
    drawLineAction->setChecked(true);
    group->addAction(drawLineAction);       //add the action to the action group
    bar->addAction(drawLineAction);         //add the action to the tool bar

    QAction *drawRectAction = new QAction("Rectangle", bar);
    drawRectAction->setIcon(QIcon(":/picture/rect.png"));
    drawRectAction->setToolTip(tr("Draw a rectangle."));
    drawRectAction->setStatusTip(tr("Draw a rectangle."));
    drawRectAction->setCheckable(true);
    group->addAction(drawRectAction);
    bar->addAction(drawRectAction);

    QAction *drawCircleAction = new QAction("Circle", bar);
    drawCircleAction->setIcon(QIcon(":/picture/circle.png"));
    drawCircleAction->setToolTip(tr("Draw a circle."));
    drawCircleAction->setStatusTip(tr("Draw a circle."));
    drawCircleAction->setCheckable(true);
    group->addAction(drawCircleAction);
    bar->addAction(drawCircleAction);

    QAction *StartDequeueAction = new QAction("StartDequeue", bar);
    StartDequeueAction->setText("Start Dequeue");
    StartDequeueAction->setToolTip(tr("Starting dequeue."));
    StartDequeueAction->setStatusTip(tr("Starting dequeue."));
    StartDequeueAction->setCheckable(true);
    group->addAction(StartDequeueAction);
    bar->addAction(StartDequeueAction);

    QAction *DequeueAction = new QAction("Dequeue", bar);
    DequeueAction->setText("Dequeue");
    DequeueAction->setToolTip(tr("dequeue."));
    DequeueAction->setStatusTip(tr("dequeue."));
    DequeueAction->setCheckable(true);
    group->addAction(DequeueAction);
    bar->addAction(DequeueAction);

    QSpinBox* spinBox = new QSpinBox(this);     //create a spin box for the stride
    spinBox->setSingleStep(1);      //set the step value
    spinBox->setValue(1);           //set the default value
    spinBox->setPrefix("数到第");      //set the prefix and suffix
    spinBox->setSuffix("个元素删除");
    bar->addWidget(spinBox);            //add the spinbox to the tool bar

    splitter = new QSplitter();         //create a splitter for two widgets
    paintWidget = new PaintWidget(this);    //add two widgets to the splitter
    itemWidget = new QListWidget(this);
    splitter->addWidget(paintWidget);
    splitter->addWidget(itemWidget);
    setCentralWidget(splitter);         //set the splitter

    connect(spinBox, SIGNAL(valueChanged(int)),
                        this, SLOT(ChangeStride(int)));     //set the stride with spinbox

    connect(drawLineAction, SIGNAL(triggered()),
                        this, SLOT(drawLineActionTriggered()));
    connect(drawRectAction, SIGNAL(triggered()),
                        this, SLOT(drawRectActionTriggered()));
    connect(drawCircleAction, SIGNAL(triggered()),
                        this, SLOT(drawCircleActionTriggered()));
    connect(paintWidget, SIGNAL(PWReturn()),
                        this, SLOT(updateItems()));
    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
                        paintWidget, SLOT(setCurrentShape(Shape::Code)));      //set the painting tool with three actions

    connect(StartDequeueAction, SIGNAL(triggered()),
                        this, SLOT(StartDequeueActionTriggered()));     //send the start signal to paintwidget
    connect(this, SIGNAL(startdequeue()),
                        paintWidget, SLOT(StopDrawing()));

    connect(DequeueAction, SIGNAL(triggered()),
                        this, SLOT(DequeueActionTriggered()));
    connect(this, SIGNAL(dequeue(int)),
                        paintWidget, SLOT(Dequeue(int)));       //send the dequeue signal to paingwidget
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineActionTriggered()
{
    emit changeCurrentShape(Shape::Line);
}

void MainWindow::drawRectActionTriggered()
{
    emit changeCurrentShape(Shape::Rect);
}

void MainWindow::drawCircleActionTriggered()
{
    emit changeCurrentShape(Shape::Circle);
}

//update the list of geometries
void MainWindow::updateItems()
{
    //reset the starting serial number
    itemWidget->clear();
    //iterate through the shapeList and get the serial number
    QList<Shape*>::iterator it =  paintWidget->shapeList.begin();
    for(;it!=paintWidget->shapeList.end();it++)
    {
        int n = (*it)->GetNum();
        std::string s = "Shape ";
        s += std::to_string(n);
        itemWidget->addItem(s.c_str());
    }
}

void MainWindow::StartDequeueActionTriggered()
{
    emit startdequeue();
}

//update the stride
void MainWindow::ChangeStride(int n)
{
    stride = n;
}

void MainWindow::DequeueActionTriggered()
{
    emit dequeue(stride);
}
