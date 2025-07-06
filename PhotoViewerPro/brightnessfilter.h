#ifndef BRIGHTNESSFILTER_H
#define BRIGHTNESSFILTER_H

#include "constants.h"
#include "filter.h"

#include <QColor>


class BrightnessFilter : public Filter {
public:
    BrightnessFilter(int brightnessOffset = START_VALUE);

    /**
     * @brief applies filter to picture
     * @param 'image' original picture
     * @return filtered picture
     */

    QImage apply(const QImage& image) const override;

    /**
     * @brief sets the changing brightness level
     * @param 'offset' brightness change value
     */

    void setBrightnessOffset(int offset);

    /**
     * @brief gets the changing brightness level
     * @return brightness change value
     */

    inline int getBrightnessOffset() const {return m_brightnessOffset;}

private:
    int m_brightnessOffset;
};


#endif // BRIGHTNESSFILTER_H
