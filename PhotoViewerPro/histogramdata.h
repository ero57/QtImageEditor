#ifndef HISTOGRAMDATA_H
#define HISTOGRAMDATA_H

#include "constants.h"

#include <array>
#include <QImage>
#include <QVector>


class HistogramData {
public:

    /**
     * @brief calculates pixel color count for histogram
     * @param 'image' is the current live image
     */

    void calculate(const QImage& image);

    const QVector<double>& red() const { return m_red; }
    const QVector<double>& green() const { return m_green; }
    const QVector<double>& blue() const { return m_blue; }

private:
    QVector<double> m_red, m_green, m_blue;
};


#endif
