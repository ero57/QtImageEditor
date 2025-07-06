#include "filterwidget.h"


FilterWidget::FilterWidget(QWidget *parent)
    : QWidget(parent)
{
    // --- create sliders and labels ---
    m_brightnessSlider = new QSlider(Qt::Horizontal, this);
    m_gaussianSlider = new QSlider(Qt::Horizontal, this);
    m_negativCheckBox = new QCheckBox("Activate", this);
    m_sepiaSlider = new QSlider(Qt::Horizontal, this);

    // --- set slider intervals ---
    m_brightnessSlider->setRange(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
    m_gaussianSlider->setRange(START_VALUE, MAX_BLUR_GRAIN);
    m_sepiaSlider->setRange(START_VALUE, MAX_SEPIA_STRENGTH);

    // --- set all sliders 0 ---
    m_brightnessSlider->setValue(START_VALUE);
    m_gaussianSlider->setValue(START_VALUE);
    m_sepiaSlider->setValue(START_VALUE);
    // --- deactivate checkbox ---
    m_negativCheckBox->setChecked(false);


    // --- labels for slider names ---
    m_brightnessLabel = new QLabel("Brightness:", this);
    m_gaussianLabel = new QLabel("Gaussian Blur:", this);
    m_negativLabel = new QLabel("Negative:", this);
    m_sepiaLabel = new QLabel("Sepia:", this);

    // --- labels for slider values ---
    m_brightnessValueLabel = new QLabel("0", this);
    m_gaussianValueLabel = new QLabel("0", this);
    m_sepiaValueLabel = new QLabel("0", this);

    // --- create layout ---
    auto *mainLayout = new QVBoxLayout(this);

    // --- groupbox for better visibility ---
    auto *groupBox = new QGroupBox("Image Filters", this);
    auto *groupLayout = new QVBoxLayout(groupBox);

    // --- brightness layout ---
    auto *brightnessLayout = new QHBoxLayout();
    brightnessLayout->addWidget(m_brightnessLabel);
    brightnessLayout->addWidget(m_brightnessSlider);
    brightnessLayout->addWidget(m_brightnessValueLabel);

    // --- gaussian layout ---
    auto *gaussianLayout = new QHBoxLayout();
    gaussianLayout->addWidget(m_gaussianLabel);
    gaussianLayout->addWidget(m_gaussianSlider);
    gaussianLayout->addWidget(m_gaussianValueLabel);

    // --- negativ layout ---
    auto *negativLayout = new QHBoxLayout();
    negativLayout->addWidget(m_negativLabel);
    negativLayout->addWidget(m_negativCheckBox);

    // --- sepia layout ---
    auto *sepiaLayout = new QHBoxLayout();
    sepiaLayout->addWidget(m_sepiaLabel);
    sepiaLayout->addWidget(m_sepiaSlider);
    sepiaLayout->addWidget(m_sepiaValueLabel);

    // --- add all layouts to groupbox ---
    groupLayout->addLayout(brightnessLayout);
    groupLayout->addLayout(gaussianLayout);
    groupLayout->addLayout(negativLayout);
    groupLayout->addLayout(sepiaLayout);

    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);

    // --- UPDATE VALUES ---
    // --- brightness ---
    connect(m_brightnessSlider, &QSlider::valueChanged, this, [=](int value) {
        m_brightnessValueLabel->setText(QString::number(value));
    });

    // --- gaussian ---
    connect(m_gaussianSlider, &QSlider::valueChanged, this, [=](int value) {
        m_gaussianValueLabel->setText(QString::number(value));
    });

    // --- sepia ---
    connect(m_sepiaSlider, &QSlider::valueChanged, this, [=](int value) {
        m_sepiaValueLabel->setText(QString::number(value));
    });

    connect(m_brightnessSlider, &QSlider::sliderReleased, this, &FilterWidget::emitFilterSettingsChanged);
    connect(m_sepiaSlider, &QSlider::sliderReleased, this, &FilterWidget::emitFilterSettingsChanged);
    connect(m_gaussianSlider, &QSlider::sliderReleased, this, &FilterWidget::emitFilterSettingsChanged);
    connect(m_negativCheckBox, &QCheckBox::toggled, this, &FilterWidget::emitFilterSettingsChanged);
}

int FilterWidget::getBrightnessValue() const { return currentSettings.brightness; }
int FilterWidget::getSepiaValue() const { return currentSettings.sepia; }
int FilterWidget::getGaussValue() const { return currentSettings.blur; }
bool FilterWidget::getNegativeStatus() const { return currentSettings.negative; }

void FilterWidget::onBrightnessChanged(int value) {
    currentSettings.brightness = value;
    emitFilterSettingsChanged();
}

void FilterWidget::onSepiaChanged(int value) {
    currentSettings.sepia = value;
    emitFilterSettingsChanged();
}

void FilterWidget::onGaussChanged(int value) {
    currentSettings.blur = value;
    emitFilterSettingsChanged();
}

void FilterWidget::onNegativeChanged(bool checked) {
    currentSettings.negative = checked;
    emitFilterSettingsChanged();
}

void FilterWidget::emitFilterSettingsChanged() {
    FilterSettings settings;
    settings.brightness = m_brightnessSlider->value();
    settings.sepia = m_sepiaSlider->value();
    settings.blur = m_gaussianSlider->value();
    settings.negative = m_negativCheckBox->isChecked();
    emit filterSettingsChanged(settings);
}
