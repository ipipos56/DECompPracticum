#include "view.h"
#include "ui_mainwindow.h"
#include "controller.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVector<QColor> qpens{Qt::red, Qt::blue};
    QVector<QString> names{"Exact", "Euler"};

    ui->plot->legend->setVisible(true);
    ui->plot->legend->setRowSpacing(-3);
    ui->plot->legend->setFont(QFont("Helvetica", 9));

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->setMargins(QMargins(2, 0, 2, 2));
    subLayout->addElement(0, 0, ui->plot->legend);

    ui->plot->legend->setFillOrder(QCPLegend::foColumnsFirst);
    ui->plot->plotLayout()->setRowStretchFactor(1, 0.001);

    for(int i = 0;i<2;i++)
    {
        ui->plot->addGraph();
        ui->plot->graph(i)->setScatterStyle(QCPScatterStyle::ssDot);
        ui->plot->graph(i)->setLineStyle(QCPGraph::lsLine);
        ui->plot->graph(i)->setPen(qpens[i]);
        ui->plot->graph(i)->setName(names[i]);
    }
}

View::~View()
{
    delete ui;
}


void View::addPoints(int plotIndex, QVector<double> x, QVector<double> y)
{
    setData(plotIndex, x,y);
}

void View::setData(int plotIndex, QVector<double> x, QVector<double> y)
{
    ui->plot->graph(plotIndex)->setData(x, y);
    ui->plot->graph(plotIndex)->rescaleAxes();
}

void View::plot()
{
    ui->plot->replot();
    ui->plot->update();
}


void View::getValuesFromBoxes()
{
    Controller::takeValuesFromBoxes(ui->bx_x0->value(), ui->bx_y0->value(), ui->bx_N->value(), ui->bx_X->value());
}

