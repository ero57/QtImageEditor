#include "histogramwidget.h"


HistogramWidget::HistogramWidget(QWidget* parent) : QWidget(parent) {
    m_layout = new QVBoxLayout(this);
    m_plotR = new QCustomPlot();
    m_plotG = new QCustomPlot();
    m_plotB = new QCustomPlot();

    setupPlots();
    m_layout->addWidget(m_plotR);
    m_layout->addWidget(m_plotG);
    m_layout->addWidget(m_plotB);
}

void HistogramWidget::setupPlots() {
    for (auto* plot : { m_plotR, m_plotG, m_plotB }) {
        plot->addGraph();
        plot->xAxis->setLabel("Value (0-255)");
        plot->xAxis->setRange(MIN_COLOR_VALUE, MAX_COLOR_VALUE);
        plot->yAxis->setLabel("Bitcount");
    }
}

void HistogramWidget::setHistogramData(const HistogramData& data) {
    QVector<double> x(MAX_HISTOGRAM_X_VALUE);
    for (int i = START_VALUE; i < MAX_HISTOGRAM_X_VALUE; ++i) x[i] = i;

    updatePlot(m_plotR, data.red(), Qt::red, "Red");
    updatePlot(m_plotG, data.green(), Qt::green, "Green");
    updatePlot(m_plotB, data.blue(), Qt::blue, "Blue");
}

void HistogramWidget::updatePlot(QCustomPlot* plot, const QVector<double>& yData, const QColor& color, const QString& title) {
    QVector<double> x(MAX_HISTOGRAM_X_VALUE);
    for (int i = START_VALUE; i < MAX_HISTOGRAM_X_VALUE; ++i) x[i] = i;

    // --- set data ---
    plot->graph(START_VALUE)->setData(x, yData);
    plot->graph(START_VALUE)->setPen(QPen(color));
    double maxY = *std::max_element(yData.begin() + 1, yData.end());
    plot->yAxis->setRange(START_VALUE, std::max(1.0, maxY));

    QCPLayoutGrid* layout = plot->plotLayout();

    if (layout->rowCount() > START_VALUE) {
        QCPLayoutElement* existing = layout->element(START_VALUE, START_VALUE);
        if (existing && qobject_cast<QCPTextElement*>(existing)) {
            layout->takeAt(START_VALUE);
            layout->simplify();
        }
    }

    // --- add new headline ---
    layout->insertRow(START_VALUE);
    layout->addElement(START_VALUE, START_VALUE, new QCPTextElement(plot, title, QFont("Arial", 12)));

    plot->replot();

    // --- window settings ---
    setWindowTitle("Histogram");
    resize(INIT_HISTOGRAM_WIDTH, INIT_HISTOGRAM_HEIGHT);

}

