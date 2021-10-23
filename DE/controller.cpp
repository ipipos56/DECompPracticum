#include "view.h"
#include "ui_mainwindow.h"
#include "controller.h"


Controller::Controller(View *w)
{
   this->w = w;
}


void Controller::takeValuesFromBoxes(double x0, double y0, double N, double X)
{
    w->plot();
}

