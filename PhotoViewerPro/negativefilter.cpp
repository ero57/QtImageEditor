#include "negativefilter.h"


NegativeFilter::NegativeFilter(){}

QImage NegativeFilter::apply(const QImage& image) const {
    qDebug() << "Negative applied";
    qDebug() << "Original format:" << image.format();

    // --- convert to and work on a copy ---
    QImage result = image.convertToFormat(QImage::Format_ARGB32);

    for (int y = START_VALUE; y < result.height(); ++y) {
        for (int x = START_VALUE; x < result.width(); ++x) {
            QColor color = result.pixelColor(x, y);

            int r = MAX_COLOR_VALUE - color.red();
            int g = MAX_COLOR_VALUE - color.green();
            int b = MAX_COLOR_VALUE - color.blue();
            int a = color.alpha();  // keep alpha (transparency)

            result.setPixelColor(x, y, QColor(r, g, b, a));
        }
    }

    return result;
}
