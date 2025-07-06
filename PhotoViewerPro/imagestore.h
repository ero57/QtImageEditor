#ifndef IMAGESTORE_H
#define IMAGESTORE_H

#include "constants.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QImage>


class ImageStore {
public:
    // --- Singleton-Access (static method, returns the only instnce) ---
    static ImageStore& instance();

    /**
     * @brief sets original image
     * @param 'image' is original image
     */

    void setOriginalImage(const QImage& image);

    /**
     * @brief sets processed image
     * @param 'image' is processed image
     */

    void setProcessedImage(const QImage& image);

    /**
     * @brief loads image
     * @param 'filePath' image name and location
     * @return chosen image
     */

    bool loadImage(const QString& filePath);

    /**
     * @brief saves image
     * @param 'filePath' new image name and location
     * @return success or error
     */

    bool saveImage(const QString& filePath) const;

    /**
     * @brief gets original image
     * @return original image
     */

    inline const QImage& getOriginalImage() const { return m_originalImage; }

    /**
     * @brief gets processed image
     * @return processed image
     */

    inline const QImage& getProcessedImage() const { return m_processedImage; }

private:
    ImageStore() = default; // cobstructor private so no further instances can be created
    ImageStore(const ImageStore&) = delete; // deletes copy constructor
    ImageStore& operator=(const ImageStore&) = delete; // deletes assignment

    QImage m_originalImage;
    QImage m_processedImage;
};


#endif // IMAGESTORE_H
