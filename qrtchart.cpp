#include "qrtchart.h"

QRTChart::QRTChart()
{
    setAntialiasing(true);
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    srand(time(NULL));
    QDateTime now = QDateTime::currentDateTime();
    for (int i = 0; i < 4; i++) {
        currentTime_.push_back(QDateTime());
        currentTime_[i] = now;
        tdata_.push_back(QVector<Vertex>());
        rdata_.push_back(QPolygonF());
        points_.push_back(QPolygonF());
        tdata_[i] << Vertex(currentTime_[i], rand() % 200);
    }
    yReScale();
    connect(&timer_, &QTimer::timeout, this, &QRTChart::onTimer);
    timer_.start(10);
}

void QRTChart::paint(QPainter *painter)
{
    xUnit_ = (width() - leftMargin_ - rightMargin_) / xUnitCount_;
    yUnit_ = (height() - topMargin_ - bottomMargin_) / yUnitCount_;

    bottom_ = height() - bottomMargin_;
    right_ = width() - rightMargin_;

    drawAxis(painter);
    for (int i = 0; i < 4; i++) {
        regenData(tdata_[i], rdata_[i], currentTime_[i]);
        dataToPoints(rdata_[i], points_[i]);
        painter->setPen(QPen(colors_[i], 2, Qt::SolidLine));
        painter->drawPolyline(points_[i]);
    }
}

void QRTChart::regenData(QVector<Vertex> &tdata, QPolygonF &rdata,
                         QDateTime &currentTime)
{
    QDateTime rightTime = QDateTime::currentDateTime();
    QDateTime leftTime = rightTime.addSecs(-21);
    if (currentTime.secsTo(rightTime) >= 1) {
        currentTime = rightTime;
        tdata << Vertex(currentTime, rand() % 200);
        yReScale();
    }

    if (leftTime.secsTo(tdata.first().dateTime) < -1) {
        tdata.removeFirst();
    }

    rdata.clear();
    qreal x;
    for (Vertex v : tdata) {
        x = leftTime.msecsTo(v.dateTime) / 2000.0;
        rdata << QPointF(x, v.value);
    }
}

void QRTChart::dataToPoints(QPolygonF &rdata, QPolygonF &points)
{
    points.clear();
    qreal x, y;
    for (int i = 0; i <rdata.size(); i++) {
        if (rdata[i].x() > leftBorder_ && rdata[i].x() <= rightBorder_) {
            points << transformCoord(rdata[i].x(), rdata[i].y());
        }
        if (i < rdata.size() - 1) {
            if (rdata[i].x() < leftBorder_ && rdata[i + 1].x() > leftBorder_) {
                x = leftBorder_ + 0.02;
                y = calcY3(rdata[i], rdata[i + 1], x);
                points << transformCoord(x, y);
            }
            else if (rdata[i].x() < rightBorder_ && rdata[i + 1].x() > rightBorder_) {
                x = rightBorder_;
                y = calcY3(rdata[i], rdata[i + 1], x);
                points << transformCoord(x, y);
            }
        }
    }
}

QPointF QRTChart::transformCoord(qreal x, qreal y)
{
    qreal tx = (x * xUnit_) / xDimension_ + leftMargin_;
    qreal ty = bottom_ - (y * yUnit_) / yDimension_;
    return QPointF(tx, ty);
}

qreal QRTChart::calcY3(const QPointF &p1, const QPointF &p2, qreal x3)
{
    qreal x1 = p1.x();
    qreal y1 = p1.y();
    qreal x2 = p2.x();
    qreal y2 = p2.y();
    if (x2 - x1 == 0) return 0;
    return ((x3 - x1) * (y2 - y1)) / (x2 - x1) + y1;
}

void QRTChart::onTimer()
{
    update();
}

void QRTChart::drawAxis(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    painter->drawLine(leftMargin_, topMargin_, leftMargin_, bottom_);
    painter->drawLine(leftMargin_, bottom_, right_, bottom_);
    painter->drawLine(right_, bottom_, right_, topMargin_);
    painter->drawLine(right_, topMargin_, leftMargin_, topMargin_);

    painter->setPen(QPen(Qt::gray, 1.0, Qt::DotLine));
    for (int y = topMargin_ + yUnit_; y < bottom_; y += yUnit_) {
        painter->drawLine(leftMargin_, y, right_, y);
    }

    for (qreal x = leftMargin_+ xUnit_;  x < right_; x += xUnit_) {
        painter->drawLine(x, topMargin_, x, bottom_);
    }

    size_t yLegendCounter = 0;
    painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    for (int y = bottom_; y >= topMargin_; y -= yUnit_) {
        if (yLegendCounter % yLegendStep_ == 0) {
            painter->drawText(QPoint(leftMargin_ - 40, y),
                              QString("%1")
                              .arg(yLegendCounter * yDimension_, 0, 'f', 0));
        }
        yLegendCounter++;
    }

    QDateTime leftTimePoint = currentTime_[0].addSecs(-21);
    size_t xLegendCounter = 0;
    for (qreal x = leftMargin_; x <= right_; x += xUnit_) {
        if (xLegendCounter % xLegendStep_ == 0) {
            painter->drawText(QPoint(x - 30, bottom_ + 30),
                              leftTimePoint.addSecs(xLegendCounter * 2)
                              .toString("hh:mm:ss"));
        }
        xLegendCounter++;
    }
}

void QRTChart::yReScale()
{
    qreal max = 0;
    for (QVector<Vertex> tdata : tdata_) {
        for (Vertex v : tdata) {
            max = qMax(max, v.value);
        }
    }
    yDimension_ = (1.1 * max) / 5;
}
