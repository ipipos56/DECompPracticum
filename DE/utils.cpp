#include "utils.h"

Utils::Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

Utils::Point::Point()
{
    this->x = -1;
    this->y = -1;
}


Utils::GUIValues::GUIValues(bool GUIState, double x0, double y0, double N, double X, double n0, double N2, bool ES, bool EM, bool IEM, bool RK)
{
    this->GUIState = GUIState;
    this->n0 = n0;
    this->x0 = x0;
    this->y0 = y0;
    this->N = N;
    this->N2 = N2;
    this->X = X;
    for(int t = 0;t<4;t++)
        this->buttonsCheckState[t] = false;
    if(ES)
        this->buttonsCheckState[0] = true;
    if(EM)
        this->buttonsCheckState[1] = true;
    if(IEM)
        this->buttonsCheckState[2] = true;
    if(RK)
        this->buttonsCheckState[3] = true;
}

Utils::GUIValues::GUIValues()
{
    this->GUIState = false;
    this->n0 = -1;
    this->x0 = -1;
    this->y0 = -1;
    this->N = -1;
    this->N2 = -1;
    this->X = -1;
    for(int t = 0;t<4;t++)
        this->buttonsCheckState[t] = false;
}


Utils::ModelValues::ModelValues()
{
    this->x0 = -1;
    this->y0 = -1;
    this->n = -1;
    this->h = -1;
    this->X = -1;
    this->c1 = -1;
}

Utils::ModelValues::ModelValues(double c1, double h, int n, double x0, double y0, int X)
{
    this->x0 = x0;
    this->y0 = y0;
    this->n = n;
    this->h = h;
    this->X = X;
    this->c1 = c1;
}
