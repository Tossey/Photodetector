#include "headers/spectrum.h"

Spectrum readFromFile(QFile* file)
{
    QTextStream in(file);
    Spectrum out;
    while (!in.atEnd()) {
        QString line = in.readLine();
        // В CSV файлах европейского формата децимальным разделителем является запятая, но также встречается и точка
        // Ищем в строке запятую и если она есть меняем её на точку
        line.replace(QChar(','), QString('.'));
        // Считываем из строки длину волны и значение спектральной х-ки
        QTextStream ss(&line);
        LengthWave l;
        QuantitySpectrum q;
        char ch;
        ss >> l >> ch >> q;

        out[l] = q;
    }
    return out;
}

const Spectrum* maxElements(const Spectrum& s1, const Spectrum& s2)
{
    auto size1 = s1.size();
    auto size2 = s2.size();
    if (size1 >= size2)
        return &s1;
    return &s2;
}

const Spectrum* minElements(const Spectrum& s1, const Spectrum& s2)
{
    auto size1 = s1.size();
    auto size2 = s2.size();
    if (size1 >= size2)
        return &s2;
    return &s1;
}

Spectrum multiply(const Spectrum& s1, const Spectrum& s2)
{
    Spectrum result;
    const Spectrum* max = maxElements(s1, s2);
    const Spectrum* min = minElements(s1, s2);

    for (auto it = min->begin(); it != min->end(); ++it) {
        LengthWave lengthByMin = it.key();
        QuantitySpectrum quantityByMin = it.value();
        if (min->contains(lengthByMin)) {
            QuantitySpectrum quantityByMax = max->value(lengthByMin);
            result.insert(lengthByMin, quantityByMax * quantityByMin);
        }
    }
    return  result;
}

double quadrature(const Spectrum& s)
{
    double result = 0.0;
    int i = 0;
    for (auto it = s.begin(); it != s.end(); ++it, ++i) {
        if (i == 0 || i == s.size() - 1) {
            result += it.value();
        }
        else if (i % 2 == 0) {
            result += 2.0 * it.value();
        }
        else {
            result += 4.0 * it.value();
        }
    }
    double step = (s.lastKey() - s.firstKey()) / (s.size() - 1.0);
    result *= step / 3.0;
    return  result;
}
