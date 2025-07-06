#include "gaussianblurfilter.h"


// --- because std::clamp() doesnt work ---
template <typename T>
T clamp(const T& val, const T& low, const T& high) {
    return std::max(low, std::min(val, high));
}

GaussianBlurFilter::GaussianBlurFilter(int blurGrain)
    : m_blurGrain(blurGrain) {}

void GaussianBlurFilter::setBlurGrain(int grain) {
    m_blurGrain = grain;
}

std::vector<float> generateGaussianKernel(int radius) {
    std::vector<float> kernel(2 * radius + 1);
    float sigma = radius / 2.0f;
    float sum = 0.0f;

    for (int i = -radius; i <= radius; ++i) {
        float value = std::exp(-(i * i) / (2 * sigma * sigma));
        kernel[i + radius] = value;
        sum += value;
    }

    // --- normalize ---
    for (float& val : kernel)
        val /= sum;

    return kernel;
}

QImage GaussianBlurFilter::apply(const QImage& image) const {
    if (m_blurGrain <= START_VALUE)
        return image;

    int radius = m_blurGrain;
    auto kernel = generateGaussianKernel(radius);

    QImage temp(image.size(), QImage::Format_RGB32);
    QImage result(image.size(), QImage::Format_RGB32);

    // --- horizontal blur ---
    for (int y = START_VALUE; y < image.height(); ++y) {
        for (int x = START_VALUE; x < image.width(); ++x) {
            float r = START_VALUE, g = START_VALUE, b = START_VALUE;
            float sum = START_VALUE;

            for (int k = -radius; k <= radius; ++k) {
                int nx = clamp(x + k, START_VALUE, image.width() - 1);
                QColor color = image.pixelColor(nx, y);
                float weight = kernel[k + radius];

                r += color.red() * weight;
                g += color.green() * weight;
                b += color.blue() * weight;
                sum += weight;
            }

            temp.setPixelColor(x, y, QColor(int(r / sum), int(g / sum), int(b / sum)));
        }
    }

    // --- vertical blur ---
    for (int y = START_VALUE; y < image.height(); ++y) {
        for (int x = START_VALUE; x < image.width(); ++x) {
            float r = START_VALUE, g = START_VALUE, b = START_VALUE;
            float sum = START_VALUE;

            for (int k = -radius; k <= radius; ++k) {
                int ny = clamp(y + k, START_VALUE, image.height() - 1);
                QColor color = temp.pixelColor(x, ny);
                float weight = kernel[k + radius];

                r += color.red() * weight;
                g += color.green() * weight;
                b += color.blue() * weight;
                sum += weight;
            }
            result.setPixelColor(x, y, QColor(int(r / sum), int(g / sum), int(b / sum)));
        }
    }
    return result;
}
