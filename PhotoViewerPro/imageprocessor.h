#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "brightnessfilter.h"
#include "constants.h"
#include "filtersettings.h"
#include "gaussianblurfilter.h"
#include "negativefilter.h"
#include "sepiafilter.h"

#include <QImage>


class ImageProcessor {
public:

    /**
     * @brief applies all filters when input is released
     * @param 'input' any of the fliter sliders and the negative checkbox
     * @param 'settings' current filter settings
     * @return filtered image
     */

    QImage applyFilters(const QImage& input, const FilterSettings& settings);

private:
    BrightnessFilter brightnessFilter;
    SepiaFilter sepiaFilter;
    GaussianBlurFilter gaussFilter;
    NegativeFilter negativeFilter;
};


#endif // IMAGEPROCESSOR_H
