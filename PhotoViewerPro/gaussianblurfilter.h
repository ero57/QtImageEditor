#ifndef GAUSSIANBLURFILTER_H
#define GAUSSIANBLURFILTER_H

#include "constants.h"
#include "filter.h"

#include <QImage>


class GaussianBlurFilter : public Filter {
public:
    GaussianBlurFilter(int blurGrain = START_VALUE);

    /**
     * @brief applies filter to picture
     * @param 'image' original picture
     * @return filtered picture
     */

    QImage apply(const QImage& image) const override;

    /**
     * @brief sets the changing gauss blur grain radius
     * @param 'grain' radius of blur grain
     */

    void setBlurGrain(int grain);

    /**
     * @brief gets the changing gauss blur grain radius
     * @return gauss change value
     */

    inline int getBlurGrain() const {return m_blurGrain;}

private:
    int m_blurGrain;
};


#endif // GAUSSIANBLURFILTER_H

