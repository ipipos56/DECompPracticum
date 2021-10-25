#include "controller.h"


Controller::Controller(View *w, Model::Updater *u)
{
   this->w = w;
   this->u = u;
}

void Controller::setDataAndPlot(int plotIndex, int graphIndex, std::vector<Utils::Point> points)
{
    w->addPoints(plotIndex, graphIndex, points);
    w->plot(plotIndex);
}


void Controller::takeValuesFromGUIAndUpdateCalculations()
{
    Utils::GUIValues values = w->getValuesFromGUI();
    if(values != oldValues)
    {
        oldValues = values;
        if(!values.GUIState)
        {
            std::vector<std::vector<Utils::Point>> methodsPoints = u->recalculateMethods(values.x0,values.y0,values.N,values.X);
            std::vector<std::vector<Utils::Point>> errorPoints = u->recalculateLocalErrors(methodsPoints);
            std::vector<Utils::Point> emptyPoints;
            for(int mp = 0;mp<methodsPoints.size();mp++)
            {
                if(values.buttonsCheckState[mp])
                {
                    std::vector<Utils::Point> points = methodsPoints[mp];
                    setDataAndPlot(1, mp, points);
                }
                else
                    setDataAndPlot(1, mp, emptyPoints);
            }

            for(int mp = 0;mp<errorPoints.size();mp++)
            {
                if(values.buttonsCheckState[mp+1])
                {
                    std::vector<Utils::Point> points = errorPoints[mp];
                    setDataAndPlot(2, mp, points);
                }
                else
                    setDataAndPlot(2, mp, emptyPoints);
            }
        }
        else
        {
            std::vector<std::vector<Utils::Point>> outputPoints;
            std::vector<Utils::Point> emptyPoints;
            Model::Updater::resetTotalErrors();
            for(int tn = values.n0; tn <= values.N2; tn++)
            {
                std::vector<std::vector<Utils::Point>> methodsPoints = u->recalculateMethods(values.x0,values.y0,tn,values.X);
                u->recalculateTotalErrors(tn, methodsPoints);
            }
            outputPoints = Model::Updater::getTotalErrors();
            setDataAndPlot(1, 0, emptyPoints);
            for(int mp = 1;mp<outputPoints.size();mp++)
            {
                if(values.buttonsCheckState[mp])
                {
                    std::vector<Utils::Point> points = outputPoints[mp];
                    setDataAndPlot(1, mp, points);
                }
                else
                    setDataAndPlot(1, mp, emptyPoints);
            }
        }
    }
}

