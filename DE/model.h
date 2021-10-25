#ifndef MODEL_H
#define MODEL_H


#include <functional>
#include <iostream>
#include <cmath>
#include <vector>
#include <QApplication>
#include "utils.h"

class Model{
protected:
     inline static double c1 = 0;
     inline static double h = 0;
     inline static int n = 0;
     inline static double x0 = 0;
     inline static double y0 = 0;
     inline static int X = 0;

public:

    static Utils::ModelValues getValues();
    static void setValues(double c1, double h, int n, double x0, double y0, int X);

    class Function{
    public:
        virtual double calculateStep(double tt, double yt)=0;

    };

    class MyFunction : public Function{
    public:
        MyFunction();
        double calculateStep(double tt, double yt);
    };

    class NumericalMethod{
    public:
        virtual std::vector<Utils::Point> calculateMethod(int n)=0;
        static std::vector<Utils::Point> calculateLocalError(std::vector<Utils::Point> exactPoints, std::vector<Utils::Point> methodPoints);
        static Utils::Point calculateTotalError(int N, std::vector<Utils::Point> exactPoints, std::vector<Utils::Point> methodPoints);

    };

    class EulerMethod : public NumericalMethod{
    public:
        EulerMethod();
        std::vector<Utils::Point> calculateMethod(int n);
    };

    class ImprovedEulerMethod : public NumericalMethod{
    public:
        ImprovedEulerMethod();
        std::vector<Utils::Point> calculateMethod(int n);
    };

    class RungeKutta : public NumericalMethod{
    public:
        RungeKutta();
        std::vector<Utils::Point> calculateMethod(int n);
    };

    class Updater{
    private:
        inline static std::vector<std::vector<Utils::Point>> totalErrors;
    public:
        inline static MyFunction *funct;
        Updater();
        std::vector<std::vector<Utils::Point>> recalculateMethods(double x0, double y0, double N, double X);
        std::vector<std::vector<Utils::Point>> recalculateLocalErrors(std::vector<std::vector<Utils::Point>> methodPoints);
        void recalculateTotalErrors(int N, std::vector<std::vector<Utils::Point>> methodPoints);
        static void resetTotalErrors();
        static std::vector<std::vector<Utils::Point>> getTotalErrors();
    };

    class ExactSolution{
    public:
         virtual std::vector<Utils::Point> calculatePoints(int n)=0;
         static Utils::Point calculateNextStep(int stepIndex, std::function<double(double)> func);

    };

    class MyExactSolution : public ExactSolution{
    public:
        MyExactSolution();
        std::vector<Utils::Point> calculatePoints(int n);

    };

};




#endif // MODEL_H
