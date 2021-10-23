#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include "view.h"
#include "ui_mainwindow.h"


class Controller
{

private:
    inline static View *w;

public:
    Controller(View *w);


    static void takeValuesFromBoxes(double x0, double y0, double N, double X);

};
#endif // CONTROLLER_H
