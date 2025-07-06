#ifndef NEGATIVEFILTER_H
#define NEGATIVEFILTER_H

#include "constants.h"
#include "filter.h"

#include <QColor>
#include <QDebug>
#include <QImage>


class NegativeFilter : public Filter {
public:
    NegativeFilter();

    /**
     * @brief applies filter to picture
     * @param 'image' original picture
     * @return filtered picture
     */

    QImage apply(const QImage& image) const override;

};


#endif // NEGATIVEFILTER_H
