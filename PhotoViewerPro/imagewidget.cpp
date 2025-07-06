#include "imagewidget.h"


ImageWidget::ImageWidget(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    // --- title label ---
    m_titleLabel = new QLabel(title, this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");

    // --- image label ---
    m_imageLabel = new QLabel(this);
    m_imageLabel->setMinimumSize(INIT_IMAGE_WIDTH, INIT_IMAGE_HEIGHT);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setStyleSheet("QLabel { background-color: black; border: 2px solid gray; }");
    m_imageLabel->setText("No Image");
    m_imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_imageLabel->setScaledContents(false); // manuel scaling


    // --- layout ---
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_imageLabel);
    setLayout(layout);
}

void ImageWidget::setImage(const QImage& image) {
    m_currentImage = image;
    updateImageDisplay();
}

void ImageWidget::updateImageDisplay() {
    if (m_currentImage.isNull())
        return;

    QSize targetSize = m_imageLabel->size();
    QPixmap pixmap = QPixmap::fromImage(m_currentImage);
    m_imageLabel->setPixmap(pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateImageDisplay();
}


