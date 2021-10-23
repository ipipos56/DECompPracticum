#include "view.h"
#include "controller.h"

#include <QApplication>
#include <cmath>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    w.show();
    Controller control(&w);

    QVector<double> x,y;
    QVector<double> x2,y2;

    double y0=1,x0=0;
    int X=10;
    double n = 20;
    double h = (X-x0)/n;

    double c1 = (2.0 + y0-x0)/(4.0 * pow(M_E,(4.0*x0)) * (y0-x0-2.0));

    std::cout<<c1<<std::endl;

    double tt = x0, yt = y0;

    x.append(x0);
    y.append(y0);
    x2.append(x0);
    y2.append(y0);

    for(int i = 1;i<=n;i++)
    {
        x.append(x0+i*h);
        y.append((1.0/(c1*pow(M_E,4*x.back())-1.0/4.0)) + x.back() + 2);

        double m = 5 - tt * tt - yt * yt + 2 * yt * tt;

        yt = yt + h*m;
        tt = tt + h;

        x2.append(tt);
        y2.append(yt);
    }


    w.addPoints(0, x, y);
    w.addPoints(1, x2, y2);

    w.plot();

    return a.exec();
}
