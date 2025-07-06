#include "camerawidget.h"
#include <QCamera>
#include <QMediaDevices>
#include <QCameraDevice>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QImage>
#include <QPixmap>

/**
 * @brief Konstruktor: Initialisiert Kamera, GUI und Verbindungen.
 */
CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent)
{
    // --- Kamera initialisieren ---
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty()) {
        m_camera = nullptr;
    } else {
        // Verwende die erste gefundene Kamera
        m_camera = new QCamera(cameras.first(), this);
    }

    // --- Capture Session erstellen (Qt6 benötigt dies) ---
    m_captureSession = new QMediaCaptureSession(this);

    // --- Bildaufnahme-Objekt ---
    m_imageCapture = new QImageCapture(this);

    // --- Kamera und ImageCapture mit der Session verbinden ---
    if (m_camera) {
        m_captureSession->setCamera(m_camera);
        m_captureSession->setImageCapture(m_imageCapture);
    }

    // --- Bildanzeige-Label konfigurieren ---
    m_imageLabel = new QLabel(this);
    m_imageLabel->setFixedSize(640, 480);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setStyleSheet("QLabel { background-color: black; }");

    // --- Capture-Button erstellen ---
    m_captureButton = new QPushButton("Capture Image", this);

    // --- Layout aufbauen ---
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_imageLabel);
    mainLayout->addWidget(m_captureButton);
    setLayout(mainLayout);

    // --- Signal-Slot-Verbindungen herstellen ---
    connect(m_captureButton, &QPushButton::clicked, this, &CameraWidget::captureImage);
    connect(m_imageCapture, &QImageCapture::imageCaptured,
            this, &CameraWidget::processCapturedImage);

    // --- Kamera starten, falls vorhanden ---
    if (m_camera) {
        m_camera->start();
    }
}

/**
 * @brief Destruktor: Stoppt die Kamera.
 */
CameraWidget::~CameraWidget()
{
    if (m_camera) {
        m_camera->stop();
        // Kein delete notwendig, da Parent `this` gesetzt wurde
        m_camera = nullptr;
    }
}

/**
 * @brief Startet die Aufnahme eines Einzelbildes.
 */
void CameraWidget::captureImage()
{
    if (m_camera && m_imageCapture) {
        // Qt6: Kein searchAndLock() mehr nötig, capture() ist einfacher
        m_imageCapture->capture();   // Löst die Aufnahme aus
    }
}

/**
 * @brief Verarbeitet das aufgenommene Bild (verstärkt z. B. den Blaukanal).
 * @param id Bild-ID (wird nicht genutzt)
 * @param preview Vorschau- bzw. Originalbild (QImage)
 */
void CameraWidget::processCapturedImage(int id, const QImage &preview)
{
    Q_UNUSED(id);

    // Konvertiere das Bild in ein RGB32-Format für die Bearbeitung
    QImage rgbImage = preview.convertToFormat(QImage::Format_RGB32);

    // Faktor zur Verstärkung des Blaukanals
    const double blueFactor = 1.5;

    // Hier mal ein ganz einfaches Beispiel für einen Filter
    // Bildpixel durchlaufen und Blauwert erhöhen
    for (int y = 0; y < rgbImage.height(); ++y) {
        for (int x = 0; x < rgbImage.width(); ++x) {
            QColor color = rgbImage.pixelColor(x, y);
            int blue = color.blue();
            int newBlue = qMin(255, static_cast<int>(blue * blueFactor));
            color.setBlue(newBlue);
            rgbImage.setPixelColor(x, y, color);
        }
    }

    // Das bearbeitete Bild im Label anzeigen, skaliert auf die Labelgröße
    m_imageLabel->setPixmap(QPixmap::fromImage(rgbImage).scaled(
        m_imageLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
}
