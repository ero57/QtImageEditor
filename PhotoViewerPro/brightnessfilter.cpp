#include "brightnessfilter.h"


BrightnessFilter::BrightnessFilter(int brightnessOffset)
    : m_brightnessOffset(brightnessOffset) {}

void BrightnessFilter::setBrightnessOffset(int offset) {
    m_brightnessOffset = offset;
}

QImage BrightnessFilter::apply(const QImage& image) const {
    if(m_brightnessOffset == START_VALUE){
        return image;
    }
    QImage result = image.convertToFormat(QImage::Format_RGB32);

    for (int y = START_VALUE; y < result.height(); ++y) {
        QRgb* row = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = START_VALUE; x < result.width(); ++x) {
            QColor color = QColor::fromRgb(row[x]);

            int r = qBound(MIN_COLOR_VALUE, color.red() + m_brightnessOffset, MAX_COLOR_VALUE);
            int g = qBound(MIN_COLOR_VALUE, color.green() + m_brightnessOffset, MAX_COLOR_VALUE);
            int b = qBound(MIN_COLOR_VALUE, color.blue() + m_brightnessOffset, MAX_COLOR_VALUE);

            row[x] = qRgb(r, g, b);
        }
    }
    return result;
}
