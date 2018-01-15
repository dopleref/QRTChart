#include "qrtchart.h"
#include <QDebug>

QRTChart::QRTChart()
{
    currentTime_ = QDateTime::currentDateTime();
    srand(time(NULL));
    /*
    for (int i = 0; i < 10; i++) {
        data_ << QPointF(i, rand() % 200);
    }
    */
    data_ << QPoint(9, rand() % 200);
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
    regenData();
    dataToPoints();
    painter->setPen(QPen(Qt::green, 2, Qt::SolidLine));
    painter->drawPolyline(points_);
}

void QRTChart::regenData()
{
    data_.translate(-0.01, 0);
    qreal maxX = data_.last().x();
    if (maxX < rightBorder_) {
        data_ << QPointF(maxX + 1, rand() % 200);
    }
    qreal minX = data_.first().x();
    if (minX < leftBorder_ - 1) {
        data_.removeFirst();
    }
}

void QRTChart::dataToPoints()
{
    points_.clear();
    qreal x, y;
    for (int i = 0; i < data_.size(); i++) {
        if (data_[i].x() > leftBorder_ && data_[i].x() < rightBorder_) {
            points_ << transformCoord(data_[i].x(), data_[i].y());
        }
        if (i < data_.size() - 1) {
            if (data_[i].x() < leftBorder_ && data_[i + 1].x() > leftBorder_) {
                x = leftBorder_ + 0.02;
                y = calcY3(data_[i], data_[i + 1], x);
                points_ << transformCoord(x, y);
            }
            else if (data_[i].x() < rightBorder_ && data_[i + 1].x() > rightBorder_) {
                x = rightBorder_;
                y = calcY3(data_[i], data_[i + 1], x);
                points_ << transformCoord(x, y);
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
                              QString("%1").arg(yLegendCounter * yDimension_));
        }
        yLegendCounter++;
    }

    QDateTime now = QDateTime::currentDateTime();
    if (currentTime_.secsTo(now) >= 1) {
        currentTime_ = now;
        //qDebug() << currentTime_.toString("mm:ss:zzz");
    }
    QDateTime leftTimePoint = currentTime_.addSecs(-10);
    size_t xLegendCounter = 0;
    for (qreal x = leftMargin_; x <= right_; x += xUnit_) {
        if (xLegendCounter % xLegendStep_ == 0) {
            /*
            painter->drawText(QPoint(x, bottom_ + 30),
                              QString("%1").arg(xLegendCounter * xDimension_));
                              */
            painter->drawText(QPoint(x - 30, bottom_ + 30),
                              leftTimePoint.addSecs(xLegendCounter)
                              .toString("hh:mm:ss"));
        }
        xLegendCounter++;
    }
}
