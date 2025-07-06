#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include "constants.h"
#include "histogramdata.h"
#include "qcustomplot.h"

#include <QVBoxLayout>
#include <QWidget>


class HistogramWidget : public QWidget {

    Q_OBJECT

public:
    explicit HistogramWidget(QWidget* parent = nullptr);

    /**
     * @brief sets histogram data
     * @param 'data' all counted pixels and their color values
     */

    void setHistogramData(const HistogramData& data);

private:
    QVBoxLayout* m_layout;
    QCustomPlot* m_plotR;
    QCustomPlot* m_plotG;
    QCustomPlot* m_plotB;

    void setupPlots();
    void updatePlot(QCustomPlot* plot, const QVector<double>& yData, const QColor& color, const QString& title);
};


#endif // HISTOGRAMWIDGET_H
