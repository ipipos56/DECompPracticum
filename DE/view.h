#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

    void addPoints(int plotIndex, QVector<double> x, QVector<double> y);
    void setData(int plotIndex, QVector<double> x, QVector<double> y);
    void plot();

private slots:
    void getValuesFromBoxes();

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;
};
#endif // VIEW_H
