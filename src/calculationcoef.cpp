#include <QtWidgets>

#include "headers/calculationcoef.h"
#include "ui_calculationcoef.h"
#include "headers/spectrum.h"

CalculationCoef::CalculationCoef(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculationCoef),
    sensitivityPhotoDetector(),
    intensityLED()
{
    ui->setupUi(this);

    QFile fileSensitivityEye(":/data/eye_sens.csv");
    if (!fileSensitivityEye.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Критическая ошибка!",
                              "Повреждены внутренние данные: " + fileSensitivityEye.errorString());
        emit exit();
    }
    sensitivtyHumanEye = readFromFile(&fileSensitivityEye);

    QFile fileIntensitySourceA(":/data/ref_src.csv");
    if (!fileIntensitySourceA.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Критическая ошибка!",
                              "Повреждены внутренние данные: " + fileIntensitySourceA.errorString());
        emit exit();
    }
    intensitySourceA = readFromFile(&fileIntensitySourceA);

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
    if (!pathSpecSens.isEmpty()) {
        QFile fileSensitivityDetector(pathSpecSens);
        if (!fileSensitivityDetector.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Ошибка!",
                                 "Невозможно открыть " + fileSensitivityDetector.errorString());
            return;
        }
        ui->pathSpecSensEdit->setText(pathSpecSens);

        sensitivityPhotoDetector = readFromFile(&fileSensitivityDetector);
    }
}

void CalculationCoef::openSpectrumIntesity()
{
    QString pathSpecIntens = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "", tr("CSV (*.csv);;All files(*)"));
    if (!pathSpecIntens.isEmpty()) {
        QFile fileIntesityLED(pathSpecIntens);
        if (!fileIntesityLED.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Ошибка!",
                                 "Невозможно открыть " + fileIntesityLED.errorString());
            return;
        }
        ui->pathSpecIntensEdit->setText(pathSpecIntens);

        sensitivityPhotoDetector = readFromFile(&fileIntesityLED);
    }

}

void CalculationCoef::calculate()
{
    if (sensitivityPhotoDetector.empty()) {
        QMessageBox::warning(this, "Ошибка!",
                             "Не выбрана фотоголовка");
        return;
    }


    Spectrum firstMul = multiply(intensitySourceA, sensitivityPhotoDetector);
    double firstQuadr = quadrature(firstMul);

    Spectrum secondMul = multiply(intensityLED, sensitivtyHumanEye);
    double secondQuadr = quadrature(secondMul);

    Spectrum thirdMul = multiply(intensitySourceA, sensitivtyHumanEye);
    double thirdQuadr = quadrature(thirdMul);

    Spectrum fourthMul = multiply(intensityLED, sensitivityPhotoDetector);
    double fourthQuard = quadrature(fourthMul);

    double val = ui->doubleSpinBox->value();
    QString out;
    QTextStream ts(&out);
    ts << val;
    ui->output->setText(out);
}

void CalculationCoef::openHelp()
{

}
