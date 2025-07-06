#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include "constants.h"
#include "filtersettings.h"

#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>


class QSlider;
class QLabel;
class QCheckBox;
class QVBoxLayout;
class QHBoxLayout;

class FilterWidget : public QWidget {

    Q_OBJECT

public:
    explicit FilterWidget(QWidget *parent = nullptr);

    /**
     * @brief gets the changing brightness level
     * @return brightness change value
     */

    int getBrightnessValue() const;

    /**
     * @brief gets the changing sepia intensity
     * @return sepia change value
     */

    int getSepiaValue() const;

    /**
     * @brief gets the changing gauss blur grain radius
     * @return gauss change value
     */

    int getGaussValue() const;

    /**
     * @brief gets nagive bool status
     * @return negative activation status
     */

    bool getNegativeStatus() const;

private:
    QSlider *m_brightnessSlider;
    QSlider *m_gaussianSlider;
    QSlider *m_sepiaSlider;

    QLabel *m_brightnessLabel;
    QLabel *m_gaussianLabel;
    QLabel *m_negativLabel;
    QLabel *m_sepiaLabel;

    QLabel *m_brightnessValueLabel;
    QLabel *m_gaussianValueLabel;
    QLabel *m_sepiaValueLabel;

    QCheckBox *m_negativCheckBox;

    void emitFilterSettingsChanged();

    FilterSettings currentSettings;

signals:

    /**
     * @brief reacts to any filter slider change
     * @param 'settings' saves current filter settings
     */

    void filterSettingsChanged(const FilterSettings& settings);

private slots:
    void onBrightnessChanged(int value);
    void onSepiaChanged(int value);
    void onGaussChanged(int value);
    void onNegativeChanged(bool checked);
};


#endif
