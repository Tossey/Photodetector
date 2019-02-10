#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class CalculationCoef;
}

class CalculationCoef : public QWidget
{
    Q_OBJECT

public:
    explicit CalculationCoef(QWidget *parent = nullptr);
    ~CalculationCoef();

private slots:
    void openSpectrumSensitivity();
    void openSpectrumIntesity();

    void openHelp();

    void calculate();

signals:
    void exit();

private:
    Ui::CalculationCoef *ui;
};

#endif // WIDGET_H
