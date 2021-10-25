#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View *w = new View();
    w->show();
    Model::Grid *g = new Model::Grid();
    Controller *control = new Controller(w, g);

    while(true)
    {
        control->takeValuesFromBoxes();
        Utils::delay(100);
    }

    //QVector<double> x2,y2;

    /*
    double tt = x0, yt = y0;

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
    */

    return a.exec();
}
