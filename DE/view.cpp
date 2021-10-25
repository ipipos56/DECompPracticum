#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lb_n0->setVisible(false);
    ui->lb_N2->setVisible(false);
    ui->bx_N2->setVisible(false);
    ui->bx_n0->setVisible(false);

    //Intitialization of first plot
    ui->plot->legend->setVisible(true);
    ui->plot->legend->setRowSpacing(-3);
    ui->plot->legend->setFont(QFont("Helvetica", 8));

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->setMargins(QMargins(2, 0, 2, 2));
    subLayout->addElement(0, 0, ui->plot->legend);

    ui->plot->legend->setFillOrder(QCPLegend::foColumnsFirst);
    ui->plot->plotLayout()->setRowStretchFactor(1, 0.001);

    for(int i = 0;i<numberOfGraphs;i++)
    {
        QPen pen;
        pen.setColor(qpens[i]);
        pen.setWidthF(3);

        ui->plot->addGraph();
        ui->plot->graph(i)->setScatterStyle(QCPScatterStyle::ssDot);
        ui->plot->graph(i)->setLineStyle(QCPGraph::lsLine);
        ui->plot->graph(i)->setPen(pen);
        ui->plot->graph(i)->setName(names[i]);
    }


    //Intitialization of second plot

    for(int i = 0;i<numberOfGraphs-1;i++)
    {
        QPen pen;
        pen.setColor(qpens[i+1]);
        pen.setWidthF(3);

        ui->plot2->addGraph();
        ui->plot2->graph(i)->setScatterStyle(QCPScatterStyle::ssDot);
        ui->plot2->graph(i)->setLineStyle(QCPGraph::lsLine);
        ui->plot2->graph(i)->setPen(pen);
        ui->plot2->graph(i)->setName(names[i+1]);
    }

}

View::~View()
{
    delete ui;
}


void View::addPoints(int plotIndex, int graphIndex, std::vector<Utils::Point> points)
{
    QVector<double> x;
    QVector<double> y;
    for(auto point : points)
    {
        x.append(point.x);
        y.append(point.y);
    }
    setData(plotIndex, graphIndex, x,y);
}

void View::setData(int plotIndex, int graphIndex, QVector<double> x, QVector<double> y)
{
    if(plotIndex == 1)
    {
        ui->plot->graph(graphIndex)->setData(x, y);
        ui->plot->xAxis->rescale();
        ui->plot->yAxis->rescale();
    }
    else if(plotIndex == 2)
    {
        ui->plot2->graph(graphIndex)->setData(x, y);
        ui->plot2->xAxis->rescale();
        ui->plot2->yAxis->rescale();
    }
}

void View::plot(int plotIndex)
{
    if(plotIndex == 1)
    {
        ui->plot->replot();
        ui->plot->update();
    }
    else if(plotIndex == 2)
    {
        ui->plot2->replot();
        ui->plot2->update();
    }
}


Utils::GUIValues View::getValuesFromGUI()
{
    return Utils::GUIValues(GUIState, ui->bx_x0->value(), ui->bx_y0->value(), ui->bx_N->value(), ui->bx_X->value(), ui->bx_n0->value(), ui->bx_N2->value(), ui->ch_es->checkState(), ui->ch_em->checkState(),ui->ch_iem->checkState(), ui->ch_rk->checkState());
}

void setVisibility(bool visibility, Ui::MainWindow *ui)
{
    ui->bx_N2->setVisible(!visibility);
    ui->bx_n0->setVisible(!visibility);
    ui->bx_N->setVisible(visibility);
    ui->bx_x0->setVisible(visibility);
    ui->bx_y0->setVisible(visibility);
    ui->bx_X->setVisible(visibility);
    ui->plot2->setVisible(visibility);
    ui->ch_es->setVisible(visibility);
    ui->lb_X->setVisible(visibility);
    ui->lb_N->setVisible(visibility);
    ui->lb_x0->setVisible(visibility);
    ui->lb_y0->setVisible(visibility);
    ui->lb_m->setVisible(visibility);
    ui->lb_er->setVisible(visibility);
    ui->lb_n0->setVisible(!visibility);
    ui->lb_N2->setVisible(!visibility);
    View::GUIState = !View::GUIState;
}

void View::on_methodsButton_clicked()
{
    setVisibility(true, ui);
    ui->plot->move(20,30);
}


void View::on_totalErrorButton_clicked()
{
    setVisibility(false, ui);
    ui->plot->move(20,320);
}

