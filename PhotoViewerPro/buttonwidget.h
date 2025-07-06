#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include "constants.h"

#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>


class QPushButton;

class ButtonWidget : public QWidget {

    Q_OBJECT

public:
    explicit ButtonWidget(QWidget *parent = nullptr);

private:
    QPushButton *m_captureButton;
    QPushButton *m_showHistogramButton;
    QPushButton *m_saveImageButton;

signals:

    /**
     * @brief reacts to Load Image button clicked
     */

    void captureImageClicked();

    /**
     * @brief reacts to Save Image button clicked
     */

    void saveImageClicked();

    /**
     * @brief reacts to Show Histogram button clicked
     */

    void showHistogramClicked();
};


#endif
