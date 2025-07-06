#ifndef FILTER_H
#define FILTER_H

#include "constants.h"

#include <QImage>


/**
 * @brief abstract base class for all filters
 */

class Filter {
public:
    virtual ~Filter() = default;

    /**
     * @brief applies filter to picture
     * @param 'image' original picture
     * @return filtered picture
     */

    virtual QImage apply(const QImage& image) const = 0; // magic number (0) mandatory
};


#endif // FILTER_H
