#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPointF>

#include <QTimer>

class CustomChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qreal shift READ shift WRITE setShift NOTIFY shiftChanged)
public:
    CustomChart();

    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;

    qreal shift() const { return shift_; }

public slots:
    void init();
    void regenData();
    void setShift(qreal value);

signals:
    void shiftChanged();

private:
    void dataToPoints();
    void drawChart(QPainter* painter);
    QPointF transformCoord(qreal x, qreal y);
    void onTimer();

    void drawAxis(QPainter* painter);

    QPolygonF data_;
    QPolygonF points_;

    qreal shift_ {};

    qreal leftBorder_ = 0;
    qreal rightBorder_ = 11;

    int markupLineXstep = 100;
    int markupLineYstep = 100;

    int offsetLeft_ = 60;
    int offsetRight_ = 20;
    int offsetTop_ = 20;
    int offsetBottom_ = 100;

    QTimer timer_;

    size_t counter_ = 0;

};

#endif // CUSTOMCHART_H
