#ifndef SEPIAFILTER_H
#define SEPIAFILTER_H

#include "constants.h"
#include "filter.h"

#include <QColor>
#include <QDebug>


class SepiaFilter : public Filter {
public:
    SepiaFilter(int sepiaStrength = START_VALUE);

    /**
     * @brief applies filter to picture
     * @param 'image' original picture
     * @return filtered picture
     */

    QImage apply(const QImage& image) const override;

    /**
     * @brief sets the changing sepia intensity
     * @param 'strength' sepia change value
     */

    void setSepiaStrength(int strength);

    /**
     * @brief gets the changing sepia intensity
     * @return sepia change value
     */

    inline int getSepiaStrength() const {return m_sepiaStrength;}

private:
    int m_sepiaStrength;
};


#endif // SEPIAFILTER_H
