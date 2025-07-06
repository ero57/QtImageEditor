#include "imageprocessor.h"


QImage ImageProcessor::applyFilters(const QImage& input, const FilterSettings& settings) {
    QImage image = input;

    if (settings.sepia != START_VALUE) {
        sepiaFilter.setSepiaStrength(settings.sepia);
        image = sepiaFilter.apply(image);
    }
    if (settings.brightness != START_VALUE) {
        brightnessFilter.setBrightnessOffset(settings.brightness);
        image = brightnessFilter.apply(image);
    }
    if (settings.blur > START_VALUE) {
        gaussFilter.setBlurGrain(settings.blur);
        image = gaussFilter.apply(image);
    }
    if (settings.negative) {
        image = negativeFilter.apply(image);
    }

    return image;
}
