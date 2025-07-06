#include "histogramdata.h"


void HistogramData::calculate(const QImage& image) {
    std::array<int, MAX_HISTOGRAM_X_VALUE> red{}, green{}, blue{};
    for (int y = START_VALUE; y < image.height(); ++y) {
        for (int x = START_VALUE; x < image.width(); ++x) {
            QColor c = image.pixelColor(x, y);
            red[c.red()]++;
            green[c.green()]++;
            blue[c.blue()]++;
        }
    }

    m_red.resize(MAX_HISTOGRAM_X_VALUE);
    m_green.resize(MAX_HISTOGRAM_X_VALUE);
    m_blue.resize(MAX_HISTOGRAM_X_VALUE);
    for (int i = START_VALUE; i < MAX_HISTOGRAM_X_VALUE; ++i) {
        m_red[i] = red[i];
        m_green[i] = green[i];
        m_blue[i] = blue[i];
    }
}

