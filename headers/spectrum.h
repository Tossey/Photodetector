#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QtCore>

using LengthWave = int; // длина волна в нм
using QuantitySpectrum = double; // относительное или абсолютное значение спектральной характеристики

using Spectrum = QMap<LengthWave, QuantitySpectrum>; // набор точек, определяющий спектральную характеристику

Spectrum readFromFile(QFile* file);

#endif // SPECTRUM_H
