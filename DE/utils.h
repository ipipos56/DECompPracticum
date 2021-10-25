#ifndef UTILS_H
#define UTILS_H

#include <QTime>
#include <QApplication>

class Utils
{
public:
    struct Point{
    public:
        double x;
        double y;
        Point();
        Point(double x, double y);
    };

    struct GUIValues{
    public:
        bool GUIState;
        double n0;
        double x0;
        double y0;
        double N;
        double N2;
        double X;
        bool buttonsCheckState[4];
        GUIValues();
        GUIValues(bool GUIState, double x0, double y0, double N, double X, double n0, double N2, bool ES, bool EM, bool IEM, bool RK);
        friend bool operator!=(const GUIValues &obj1, const GUIValues &obj2) {
             return obj1.GUIState != obj2.GUIState || obj1.n0 != obj2.n0 || obj1.x0 != obj2.x0 || obj1.y0 != obj2.y0 || obj1.N != obj2.N ||
                     obj1.N2 != obj2.N2 || obj1.X != obj2.X || obj1.buttonsCheckState[0] != obj2.buttonsCheckState[0]
                     || obj1.buttonsCheckState[1] != obj2.buttonsCheckState[1] || obj1.buttonsCheckState[2] != obj2.buttonsCheckState[2]
                     || obj1.buttonsCheckState[3] != obj2.buttonsCheckState[3];
        }

    };

    struct ModelValues{
    public:
        double c1;
        double h;
        int n;
        double x0;
        double y0;
        int X;
        ModelValues();
        ModelValues(double c1, double h, int n, double x0, double y0, int X);
    };


    static void delay( int millisecondsToWait )
    {
        QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }
};

#endif // UTILS_H
