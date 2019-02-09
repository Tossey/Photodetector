#include "calculationcoef.h"
#include "ui_widget.h"

CalculationCoef::CalculationCoef(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculationCoef)
{
    ui->setupUi(this);
}

CalculationCoef::~CalculationCoef()
{
    delete ui;
}
