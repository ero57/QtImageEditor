#include "imagestore.h"


// return Singleton-Instanz
ImageStore& ImageStore::instance() {
    static ImageStore instance; // static variable: is created only once and reused afterwards
    return instance;
}

void ImageStore::setOriginalImage(const QImage& image) {
    m_originalImage = image;
}

void ImageStore::setProcessedImage(const QImage& image) {
    m_processedImage = image;
}

bool ImageStore::loadImage(const QString& filePath) {
    QImage image(filePath);
    if (!image.isNull()) {
        setOriginalImage(image);
        setProcessedImage(image);
        qDebug() << "Image loaded successfully.";
        return true;
    } else {
        qDebug() << "Error while loading image.";
        return false;
    }
}

bool ImageStore::saveImage(const QString& filePath) const {
    if (m_processedImage.isNull()) {
        qDebug() << "No image to save.";
        return false;
    }
    bool success = m_processedImage.save(filePath);
    if (success) {
        qDebug() << "Image saved successfully.";
    } else {
        qDebug() << "Error while saving image.";
    }
    return success;
}
