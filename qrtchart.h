#ifndef QRTCHART_H
#define QRTCHART_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPointF>
#include <QTimer>
#include <QDateTime>
#include <QDebug>


struct Vertex {
    QDateTime dateTime;
    qreal value;

    Vertex(QDateTime dt, qreal arg) {
        dateTime = dt;
        value = arg;
    }

    Vertex() {
        dateTime = QDateTime::currentDateTime();
        value = 0;
    }

    friend QDebug operator <<(QDebug d, Vertex v) {
        d << "Vertex(" << v.dateTime.toString("hh:mm:ss:zzz")
          << ", " << v.value << ")";
        return d;
    }

};


class QRTChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    QRTChart();
    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;

public slots:

private:
    void regenData();
    void dataToPoints();
    QPointF transformCoord(qreal x, qreal  y);
    qreal calcY3(const QPointF& p1, const QPointF& p2, qreal x3);
    void onTimer();
    void drawAxis(QPainter* painter);

    QVector<Vertex> data2_;
    QPolygonF data_;
    QPolygonF points_;

    QDateTime  currentTime_;

    qreal leftBorder_ = 0;
    qreal rightBorder_ = 10;

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

    QTimer timer_;


};

#endif // QRTCHART_H
