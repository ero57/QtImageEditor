#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>

// Forward declarations
class QCamera;
class QImageCapture;
class QMediaCaptureSession;
class QLabel;
class QPushButton;
class QImage;

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget();

private slots:
    void captureImage();
    void processCapturedImage(int id, const QImage &preview);

private:
    QCamera *m_camera;
    QImageCapture *m_imageCapture;
    QMediaCaptureSession *m_captureSession;  // Neu in Qt6
    QLabel *m_imageLabel;
    QPushButton *m_captureButton;
};

#endif // CAMERAWIDGET_H
