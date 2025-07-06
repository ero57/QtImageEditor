#include "sepiafilter.h"


SepiaFilter::SepiaFilter(int sepiaStrength)
    : m_sepiaStrength(sepiaStrength) {}

void SepiaFilter::setSepiaStrength(int strength) {
    m_sepiaStrength = strength;
}

QImage SepiaFilter::apply(const QImage& image) const {
    if(m_sepiaStrength == START_VALUE){
        return image;
    }
    if (image.isNull())
        qDebug() << "No image in ImageStore!";

    QImage sepiaImage = image; // copy original image

    for (int y = START_VALUE; y < sepiaImage.height(); ++y) {
        for (int x = START_VALUE; x < sepiaImage.width(); ++x) {
            QColor pixelColor = sepiaImage.pixelColor(x, y);
            int r = pixelColor.red();
            int g = pixelColor.green();
            int b = pixelColor.blue();

            // --- mix sepia ---
            int tr = (SEPIA_FACTOR_RED_FOR_RED_PIXEL * r + SEPIA_FACTOR_GREEN_FOR_RED_PIXEL * g + SEPIA_FACTOR_BLUE_FOR_RED_PIXEL * b) * (1 + m_sepiaStrength / 100.0);
            int tg = (SEPIA_FACTOR_RED_FOR_GREEN_PIXEL * r + SEPIA_FACTOR_GREEN_FOR_GREEN_PIXEL * g + SEPIA_FACTOR_BLUE_FOR_GREEN_PIXEL * b) * (1 + m_sepiaStrength / 100.0);
            int tb = (SEPIA_FACTOR_RED_FOR_BLUE_PIXEL * r + SEPIA_FACTOR_GREEN_FOR_BLUE_PIXEL * g + SEPIA_FACTOR_BLUE_FOR_BLUE_PIXEL * b) * (1 + m_sepiaStrength / 100.0);

            // --- limit color values to a valid interval ---
            tr = qMin(MAX_COLOR_VALUE, qMax(MIN_COLOR_VALUE, tr));
            tg = qMin(MAX_COLOR_VALUE, qMax(MIN_COLOR_VALUE, tg));
            tb = qMin(MAX_COLOR_VALUE, qMax(MIN_COLOR_VALUE, tb));

            sepiaImage.setPixelColor(x, y, QColor(tr, tg, tb));
        }
    }
return sepiaImage;
}

