#include "customchart.h"

#include <QDebug>

CustomChart::CustomChart() {}

void CustomChart::paint(QPainter *painter)
{
    regenData();
    dataToPoints();
    drawAxis(painter);
    drawChart(painter);
}

void CustomChart::init()
{
    srand(time(NULL));
    for (int i = 0; i < 11; i++) {
        data_ << QPointF(i, rand() % 200);
    }
    connect(&timer_, &QTimer::timeout, this, &CustomChart::onTimer);
    timer_.start(10);
}

void CustomChart::regenData()
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

void CustomChart::setShift(qreal value)
{
    if (shift_ == value) {
        return;
    }

    shift_ = value;
    emit shiftChanged();
}

void CustomChart::dataToPoints()
{
    points_.clear();
    qreal x3, y3;
    for (int i = 0; i < data_.size(); i++) {
        if ((i < data_.size() - 1) &&
            (data_[i].x() < leftBorder_) && (data_[i + 1].x() > leftBorder_)) {
            x3 = leftBorder_ + 0.02;
            y3 = calcY3(data_[i], data_[i + 1], x3);
            points_ << transformCoord(x3, y3);
        }
        if (data_[i].x() > leftBorder_ && data_[i].x() <= rightBorder_) {
            points_ << transformCoord(data_[i].x(), data_[i].y());
        }
        if ((i < data_.size() - 1) &&
            (data_[i].x() < rightBorder_) && (data_[i + 1].x() > rightBorder_)) {
            x3 = rightBorder_;
            y3 = calcY3(data_[i], data_[i + 1], x3);
            points_ << transformCoord(x3, y3);
        }
    }
}

qreal CustomChart::calcY3(const QPointF &p1, const QPointF &p2, qreal x3)
{
    qreal x1 = p1.x();
    qreal y1 = p1.y();
    qreal x2 = p2.x();
    qreal y2 = p2.y();
    if (x2 - x1 == 0) return 0;
    return ((x3 - x1) * (y2 - y1)) / (x2 - x1) + y1;
}

void CustomChart::drawChart(QPainter *painter)
{
    painter->setPen(QPen(Qt::green, 2, Qt::SolidLine));
    painter->drawPolyline(points_);
}

QPointF CustomChart::transformCoord(qreal x, qreal y)
{
    qreal tx = x * 100 + offsetLeft_;
    qreal ty = 500 - y * 2;
    return QPointF(tx, ty);
}

void CustomChart::onTimer()
{
    update();
    /*
    counter_++;
    if (counter_ == 100) {
        qDebug() << counter_;
        counter_ = 0;
    }
    */
}

void CustomChart::drawAxis(QPainter *painter)
{
    int bottom = height() - offsetBottom_;
    int right = width() - offsetRight_;

    painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine));
    painter->drawLine(offsetLeft_, bottom, right, bottom);
    painter->drawLine(offsetLeft_, bottom, offsetLeft_, offsetTop_);

    int yLegendCounter = 0;
    for (int y = bottom; y >= offsetTop_; y -= markupLineYstep) {
        painter->setPen(QPen(Qt::gray, 1.0, Qt::DotLine));
        if (y != bottom) {
            painter->drawLine(offsetLeft_, y, right, y);
        }
        painter->setPen(QPen(Qt::black, 1.5, Qt::SolidLine));
        painter->drawLine(offsetLeft_, y, offsetLeft_ + 5, y);

        painter->drawText(QPoint(20, y),
                          QString("%1").arg(yLegendCounter / 2));
        yLegendCounter += markupLineYstep;
    }

    int xLegendCounter = 0;
    for (int x = offsetLeft_; x < right; x += markupLineXstep) {
        painter->setPen(QPen(Qt::gray, 1.0, Qt::DotLine));
        if (x != offsetLeft_) {
            painter->drawLine(x, offsetTop_, x, bottom);
        }
        painter->setPen(QPen(Qt::black, 1.5, Qt::SolidLine));
        painter->drawLine(x, bottom, x, bottom - 5);

        painter->drawText(QPoint(x, bottom + 30),
                          QString("%1").arg(xLegendCounter));
        xLegendCounter += 1;
    }
}
