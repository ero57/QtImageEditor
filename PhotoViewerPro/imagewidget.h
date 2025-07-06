#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "constants.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>


class QLabel;

class ImageWidget : public QWidget {

    Q_OBJECT

public:
    explicit ImageWidget(const QString &title, QWidget *parent = nullptr);

    /**
     * @brief sets image into frame
     * @param 'image' original image and processed image
     */

    void setImage(const QImage& image);

    /**
     * @brief resizes image when changing window size
     * @param 'event' change in window size
     */

    void resizeEvent(QResizeEvent* event);

    /**
     * @brief updates image frame according to image size
     */

    void updateImageDisplay();

private:
    QLabel *m_titleLabel;
    QLabel *m_imageLabel;
    QImage m_currentImage;
};


#endif
