#include "headers/calculationcoef.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculationCoef c;
    c.show();
    QObject::connect(&c, SIGNAL(exit()), &a, SLOT(quit()));

    return a.exec();
}
