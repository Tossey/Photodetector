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
