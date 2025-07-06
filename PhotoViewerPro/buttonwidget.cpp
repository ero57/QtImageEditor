#include "buttonwidget.h"


ButtonWidget::ButtonWidget(QWidget *parent)
    : QWidget(parent)
{
    // --- create buttons ---
    m_captureButton = new QPushButton("Load Image", this);
    m_showHistogramButton = new QPushButton("Show Histogram", this);
    m_saveImageButton = new QPushButton("Save Image", this);

    // --- set button dimensions ---

    m_captureButton->setMinimumHeight(BUTTON_HEIGHT);
    m_showHistogramButton->setMinimumHeight(BUTTON_HEIGHT);
    m_saveImageButton->setMinimumHeight(BUTTON_HEIGHT);

    // --- layout ---
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_captureButton);
    layout->addWidget(m_showHistogramButton);
    layout->addWidget(m_saveImageButton);

    // --- add spacer so buttons stay located up ---
    layout->addItem(new QSpacerItem(SPACER_WIDTH, SPACER_HEIGHT, QSizePolicy::Minimum, QSizePolicy::Expanding));

    setLayout(layout);

    connect(m_captureButton, &QPushButton::clicked, this, &ButtonWidget::captureImageClicked);
    connect(m_saveImageButton, &QPushButton::clicked, this, &ButtonWidget::saveImageClicked);
    connect(m_showHistogramButton, &QPushButton::clicked, this, &ButtonWidget::showHistogramClicked);


}
