#include <QtWidgets>

#include "calculationcoef.h"
#include "ui_widget.h"
#include "spectrum.h"

CalculationCoef::CalculationCoef(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculationCoef)
{
    ui->setupUi(this);

    connect(ui->openSpecSensButton, SIGNAL(clicked()), this, SLOT(openSpectrumSensitivity()));
    connect(ui->openSpecIntensButton, SIGNAL(clicked()), this, SLOT(openSpectrumIntesity()));

    connect(ui->calcButton, SIGNAL(clicked()), this, SLOT(calculate()));

    connect(ui->helpButton, SIGNAL(clicked()), this, SLOT(openHelp()));
    connect(ui->exitButton, SIGNAL(clicked()), SIGNAL(exit()));

    setFixedSize(size());
}

CalculationCoef::~CalculationCoef()
{
    delete ui;
}

void CalculationCoef::openSpectrumSensitivity()
{
    QString pathSpecSens = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "", tr("CSV (*.csv);;All files(*)"));
    ui->pathSpecSensEdit->setText(pathSpecSens);

    QFile file(pathSpecSens);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Невозможно открыть файл!", file.errorString());
        return;
    }

    Spectrum sensitivity = readFromFile(&file);
    QString out;
    QTextStream ts(&out);
    for (auto it = sensitivity.begin(); it != sensitivity.end(); ++it) {
        ts << it.key() << " " << it.value() << "\n";
    }
    ui->output->setText(out);
}

void CalculationCoef::openSpectrumIntesity()
{
    QString pathSpecIntens = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "", tr("CSV (*.csv);;All files(*)"));
    ui->pathSpecIntensEdit->setText(pathSpecIntens);
}

void CalculationCoef::calculate()
{
    ui->output->setText("Hello");
}

void CalculationCoef::openHelp()
{

}
