#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include "view.h"
#include "ui_mainwindow.h"
#include "model.h"


class Controller
{

private:
    inline static View *w;
    inline static Model::Grid *g;
    inline static Utils::GUIValues oldValues = Utils::GUIValues();

public:
    Controller(View *w, Model::Grid *g);

    static void setDataAndPlot(int plotIndex, int graphIndex, std::vector<Utils::Point> points);

    static void takeValuesFromBoxes();

};
#endif // CONTROLLER_H
