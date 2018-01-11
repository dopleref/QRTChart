#ifndef QRTCHART_H
#define QRTCHART_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPointF>
#include <QTimer>


class QRTChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    QRTChart();
    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;

public slots:

private:
    QPolygonF points_;

    qreal xDimension_ = 1;
    qreal yDimension_ = 50;

    size_t xLegendStep_ = 5;
    size_t yLegendStep_ = 2;

    qreal xUnitCount_ = 10;
    qreal yUnitCount_ = 5;

    qreal leftMargin_ = 70;
    qreal rightMargin_ = 70;
    qreal topMargin_ = 70;
    qreal bottomMargin_ = 70;

    qreal bottom_;
    qreal right_;

    qreal xUnit_;
    qreal yUnit_;


};

#endif // QRTCHART_H
