#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // --- create widget instances ---
    m_filterWidget = new FilterWidget(this);
    m_originalImageWidget = new ImageWidget("Original Image", this);
    m_processedImageWidget = new ImageWidget("Processed Image", this);
    m_buttonWidget = new ButtonWidget(this);

    // --- central widget ---
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // --- main layout (horizontal: left filters, right buttons) ---
    auto *mainLayout = new QVBoxLayout(centralWidget);

    // --- layout top, filters and buttons ---
    auto *topLayout = new QHBoxLayout();
    topLayout->addWidget(m_filterWidget, 3);     // slider + checkbox     ratio 3 to 1
    topLayout->addWidget(m_buttonWidget, 1);     // capture, save etc.    ratio 1 to 3

    // --- image layout bottom (horizontal beside another) ---
    auto *imagesLayout = new QHBoxLayout();
    imagesLayout->addWidget(m_originalImageWidget, 1); //  ratio 1 to 1
    imagesLayout->addWidget(m_processedImageWidget, 1);//  ratio 1 to 1

    // --- add together ---
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(imagesLayout, 1);  // biggest room for images

    // --- window settings ---
    setWindowTitle("PhotoViewerPro");
    resize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);

    connect(m_buttonWidget, &ButtonWidget::captureImageClicked, this, &MainWindow::onCaptureImageClicked);
    connect(m_buttonWidget, &ButtonWidget::saveImageClicked, this, &MainWindow::onSaveImageClicked);
    connect(m_filterWidget, &FilterWidget::filterSettingsChanged, this, &MainWindow::onFilterSettingsChanged);
    connect(m_buttonWidget, &ButtonWidget::showHistogramClicked, this, &MainWindow::onShowHistogramClicked);

}

MainWindow::~MainWindow()
{
    // --- automatic cleanup by Qt Parent-System ---
}

void MainWindow::onCaptureImageClicked(){
    // --- open data dialog in GUI ---
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open image",
        "",
        "Images (*.png *.jpg *.bmp)"
        );

    if (filePath.isEmpty())
        return; // abort

    // --- load image via ImageStore (without GUI) ---
    if (ImageStore::instance().loadImage(filePath)) {
        m_originalImageWidget->setImage(ImageStore::instance().getOriginalImage());
        m_processedImageWidget->setImage(ImageStore::instance().getProcessedImage());
    } else {
        QMessageBox::warning(this, "Error", "Image couldn't be loaded.");
    }
}

void MainWindow::onSaveImageClicked() {
    const QImage& image = ImageStore::instance().getProcessedImage();

    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "No edited image to save!");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Save image as ...",
        "filtered_image.png",
        "PNG-Image (*.png);;JPEG-Bild (*.jpg *.jpeg);;BMP-Bild (*.bmp)"
        );

    if (filePath.isEmpty())
        return; // abort

    if (ImageStore::instance().saveImage(filePath)) {
        QMessageBox::information(this, "Success", "Image was saved successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Image couldn't be saved.");
    }
}

void MainWindow::onFilterSettingsChanged(const FilterSettings& settings) {
    QImage processed = m_processor.applyFilters(ImageStore::instance().getOriginalImage(), settings);
    ImageStore::instance().setProcessedImage(processed);
    m_processedImageWidget->setImage(processed);

    if (m_histogramWidget && m_histogramWidget->isVisible()) {
        HistogramData data;
        data.calculate(processed);
        m_histogramWidget->setHistogramData(data);
    }
}

void MainWindow::onShowHistogramClicked(){
    if (!m_histogramWidget) {
        m_histogramWidget = new HistogramWidget;
        m_histogramWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(m_histogramWidget, &QObject::destroyed, this, [this]() {
            m_histogramWidget = nullptr;
        });
    }

    HistogramData data;
    data.calculate(ImageStore::instance().getProcessedImage());
    m_histogramWidget->setHistogramData(data);
    m_histogramWidget->show();
    m_histogramWidget->raise();
}

