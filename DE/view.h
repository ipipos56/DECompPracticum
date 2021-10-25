#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "utils.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
   inline static bool GUIState = false;

    View(QWidget *parent = nullptr);
    ~View();

    void addPoints(int plotIndex, int graphIndex, std::vector<Utils::Point> points);
    void setData(int plotIndex, int graphIndex, QVector<double> x, QVector<double> y);
    void plot(int plotIndex);
    Utils::GUIValues getValuesFromGUI();

private slots:
    void on_methodsButton_clicked();

    void on_totalErrorButton_clicked();

private:
    Ui::MainWindow *ui;

    inline static int numberOfGraphs = 4;
    inline static QVector<QColor> qpens{QColor(249,65,68), QColor(248,150,30), QColor(144,190,109), QColor(39,125,161)};
    inline static QVector<QString> names{"Exact", "Euler", "Improved Euler", "Runge-Kutta"};
};
#endif // VIEW_H
