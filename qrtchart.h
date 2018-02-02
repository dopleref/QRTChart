#ifndef QRTCHART_H
#define QRTCHART_H

#include <QObject>
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

    Q_PROPERTY(QString chartName1 WRITE setChartName1)
    Q_PROPERTY(QString chartName2 WRITE setChartName2)
    Q_PROPERTY(QString chartName3 WRITE setChartName3)
    Q_PROPERTY(QString chartName4 WRITE setChartName4)
public:
    QRTChart();
    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;
    Q_INVOKABLE void append(int graphNumber, qreal value);

public slots:
    void setChartName1(QString arg) { chartName1_ = arg; }
    void setChartName2(QString arg) { chartName2_ = arg; }
    void setChartName3(QString arg) { chartName3_ = arg; }
    void setChartName4(QString arg) { chartName4_ = arg; }

private:
    void moveChart(QVector<Vertex> &tdata, QPolygonF &rdata,
                         QDateTime &currentTime);

    void regenData(QVector<Vertex>& tdata, QPolygonF& rdata,
                   QDateTime& currentTime);
    void dataToPoints(QPolygonF& rdata, QPolygonF& points);
    QPointF transformCoord(qreal x, qreal  y);
    qreal calcY3(const QPointF& p1, const QPointF& p2, qreal x3);
    void onTimer();
    void drawAxis(QPainter* painter);
    void drawLengend(QPainter *painter, qreal x, qreal y, const QColor& color, const QString& text);
    void yReScale();

    QString chartName1_ = "chart1";
    QString chartName2_ = "chart2";
    QString chartName3_ = "chart3";
    QString chartName4_ = "chart4";

    QVector<QVector<Vertex>> tdata_;
    QVector<QPolygonF> rdata_;
    QVector<QPolygonF> points_;

    QVector<QColor> colors_ {QColor(0x209fdf), QColor(0x99ca53),
                QColor(0xf6a625), QColor(0x6d5fd5)};

    QVector<QDateTime> currentTime_;

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
