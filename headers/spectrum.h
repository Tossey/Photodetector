#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QtCore>

using LengthWave = int; // длина волна в нм
using QuantitySpectrum = double; // относительное или абсолютное значение спектральной характеристики

using Spectrum = QMap<LengthWave, QuantitySpectrum>; // набор точек, определяющий спектральную характеристику

Spectrum readFromFile(QFile* file);
// Перменожает две спектральные характеристики между собой и возвращает результирующую спектр. х-ку
// Размер - min(s1.size(), s2.size())
Spectrum multiply(const Spectrum& s1, const Spectrum& s2);

#endif // SPECTRUM_H
