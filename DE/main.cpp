#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View *w = new View();
    w->show();
    Model::Updater *u = new Model::Updater();
    Controller *control = new Controller(w, u);

    while(true)
    {
        control->takeValuesFromGUIAndUpdateCalculations();
        Utils::delay(100);
    }

    return a.exec();
}
