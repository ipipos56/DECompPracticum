#include "model.h"


double calculateMyFunction(double tt, double yt)
{
    return 5.0 - tt * tt - yt * yt + 2.0 * yt * tt;
}

std::vector<std::vector<Utils::Point>> Model::Updater::recalculateMethods(double x0, double y0, double N, double X)
{
    std::vector<std::vector<Utils::Point>> methods;
    Model::setValues((2.0 + y0-x0)/(4.0 * pow(M_E,(4.0*x0)) * (y0-x0-2.0)), (X-x0)/N, N, x0, y0, X);
    Model::MyExactSolution *es = new MyExactSolution();
    methods.emplace_back(es->calculateFunction(n));
    Model::EulerMethod *em = new EulerMethod();
    methods.emplace_back(em->calculateFunction(n));
    Model::ImprovedEulerMethod *iem = new ImprovedEulerMethod();
    methods.emplace_back(iem->calculateFunction(n));
    Model::RungeKutta *rk = new RungeKutta();
    methods.emplace_back(rk->calculateFunction(n));
    return methods;
}

std::vector<std::vector<Utils::Point> > Model::Updater::recalculateLocalErrors(std::vector<std::vector<Utils::Point>> methodPoints)
{
    std::vector<std::vector<Utils::Point>> errors;
    errors.emplace_back(Model::NumericalMethod::calculateLocalError(methodPoints[0],methodPoints[1]));
    errors.emplace_back(Model::NumericalMethod::calculateLocalError(methodPoints[0],methodPoints[2]));
    errors.emplace_back(Model::NumericalMethod::calculateLocalError(methodPoints[0],methodPoints[3]));
    return errors;
}

void Model::Updater::recalculateTotalErrors(int N, std::vector<std::vector<Utils::Point>> methodPoints)
{
    totalErrors[1].emplace_back(Model::NumericalMethod::calculateTotalError(N, methodPoints[0],methodPoints[1]));
    totalErrors[2].emplace_back(Model::NumericalMethod::calculateTotalError(N, methodPoints[0],methodPoints[2]));
    totalErrors[3].emplace_back(Model::NumericalMethod::calculateTotalError(N, methodPoints[0],methodPoints[3]));
}

void Model::Updater::resetTotalErrors()
{
    totalErrors.clear();
    totalErrors.emplace_back(std::vector<Utils::Point>());
    totalErrors.emplace_back(std::vector<Utils::Point>());
    totalErrors.emplace_back(std::vector<Utils::Point>());
    totalErrors.emplace_back(std::vector<Utils::Point>());
}

std::vector<std::vector<Utils::Point> > Model::Updater::getTotalErrors()
{
    return totalErrors;
}


std::vector<Utils::Point> Model::NumericalMethod::calculateLocalError(std::vector<Utils::Point> exactPoints, std::vector<Utils::Point> methodPoints)
{
    std::vector<Utils::Point> errorPoints;
    for(int p = 0;p<exactPoints.size();p++)
    {
        if(methodPoints.size() > p)
            errorPoints.emplace_back(Utils::Point(exactPoints[p].x, abs(exactPoints[p].y-methodPoints[p].y)));
    }
    return errorPoints;
}

Utils::Point Model::NumericalMethod::calculateTotalError(int N, std::vector<Utils::Point> exactPoints, std::vector<Utils::Point> methodPoints)
{
    double maxError = 0;
    for(int p = 0;p<exactPoints.size();p++)
    {
        if(methodPoints.size() > p)
        {
            double locError = abs(exactPoints[p].y-methodPoints[p].y);
            if(maxError < locError)
                maxError = locError;
        }
    }
    return Utils::Point(N, maxError);
}



std::vector<Utils::Point> Model::EulerMethod::calculateFunction(int n)
{
   std::vector<Utils::Point> points;
   points.emplace_back(Utils::Point(x0,y0));
   double yt = y0, tt = x0;
   for(int i = 1;i<=n;i++)
   {
       double m = calculateMyFunction(tt,yt);
       yt = yt + h * m;
       tt = tt + h;
       points.emplace_back(Utils::Point(tt, yt));
   }
   return points;
}

std::vector<Utils::Point> Model::ImprovedEulerMethod::calculateFunction(int n)
{
    std::vector<Utils::Point> points;
    double yt = y0, ytt, tt = x0;
    points.emplace_back(Utils::Point(x0,y0));
    for(int i = 1;i<=n;i++)
    {
        double m = calculateMyFunction(tt,yt);
        ytt = yt + h * m;
        tt = tt + h;
        double m2 = calculateMyFunction(tt,ytt);
        yt = yt + h/2.0 * (m+m2);
        points.emplace_back(Utils::Point(tt, yt));
    }
    return points;
}

std::vector<Utils::Point> Model::RungeKutta::calculateFunction(int n)
{
    std::vector<Utils::Point> points;
    double yt = y0, tt = x0;
    points.emplace_back(Utils::Point(x0,y0));
    for(int i = 1;i<=n;i++)
    {
        double m = h * calculateMyFunction(tt,yt);
        double m2 = h * calculateMyFunction(tt + 1.0/2.0 * h , yt + 1.0/2.0 * m);
        double m3 = h * calculateMyFunction(tt + 1.0/2.0 * h , yt + 1.0/2.0 * m2);
        double m4 = h * calculateMyFunction(tt + h , yt + m3);
        yt = yt + 1.0/6.0 * (m+2*m2+2*m3+m4);
        tt = tt + h;
        points.emplace_back(Utils::Point(tt, yt));
    }
    return points;
}


std::vector<Utils::Point> Model::MyExactSolution::calculateFunction(int n)
{
    std::vector<Utils::Point> points;
    points.emplace_back(Utils::Point(x0,y0));
    for(int i = 1;i<=n;i++)
    {
        points.emplace_back(calculateNextStep(i, [](double x) -> double {
                                                                       return ((1.0/(c1*pow(M_E,4*x)-1.0/4.0)) + x + 2);
                                                                   }));
    }
    return points;
}

Utils::Point Model::ExactSolution::calculateNextStep(int stepIndex, std::function<double (double)> func)
{
    return Utils::Point(x0+stepIndex*h, func(x0+stepIndex*h));
}


void Model::setValues(double c1, double h, int n, double x0, double y0, int X)
{
    Model::x0 = x0;
    Model::y0 = y0;
    Model::n = n;
    Model::h = h;
    Model::X = X;
    Model::c1 = c1;
}


Model::Updater::Updater()
{

}

Model::EulerMethod::EulerMethod()
{

}
Model::MyExactSolution::MyExactSolution()
{

}

Model::ImprovedEulerMethod::ImprovedEulerMethod()
{

}

Model::RungeKutta::RungeKutta()
{

}
