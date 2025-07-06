#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "brightnessfilter.h"
#include "buttonwidget.h"
#include "constants.h"
#include "imageprocessor.h"
#include "filterwidget.h"
#include "gaussianblurfilter.h"
#include "histogramdata.h"
#include "histogramwidget.h"
#include "imagestore.h"
#include "imagewidget.h"
#include "negativefilter.h"
#include "sepiafilter.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>


class FilterWidget;
class ImageWidget;
class ButtonWidget;
class HistogramWidget;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    FilterWidget *m_filterWidget;
    ImageWidget *m_originalImageWidget;
    ImageWidget *m_processedImageWidget;
    ButtonWidget *m_buttonWidget;
    HistogramWidget* m_histogramWidget = nullptr;

// --- filters ---
    BrightnessFilter brightnessFilter;
    SepiaFilter sepiaFilter;
    GaussianBlurFilter gaussFilter;
    NegativeFilter negativeFilter;

    int brightness;
    int sepia;
    int blur;

    ImageProcessor m_processor;

private slots:
    void onCaptureImageClicked();
    void onSaveImageClicked();
    void onShowHistogramClicked();
    void onFilterSettingsChanged(const FilterSettings& settings);
};


#endif
