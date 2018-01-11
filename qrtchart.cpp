#include "qrtchart.h"
#include <QDebug>

QRTChart::QRTChart()
{

}

void QRTChart::paint(QPainter *painter)
{
    xUnit_ = (width() - leftMargin_ - rightMargin_) / xUnitCount_;
    yUnit_ = (height() - topMargin_ - bottomMargin_) / yUnitCount_;

    bottom_ = height() - bottomMargin_;
    right_ = width() - rightMargin_;

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

    size_t xLegendCounter = 0;
    for (qreal x = leftMargin_; x <= right_; x += xUnit_) {
        if (xLegendCounter % xLegendStep_ == 0) {
            painter->drawText(QPoint(x, bottom_ + 30),
                              QString("%1").arg(xLegendCounter * xDimension_));
        }
        xLegendCounter++;
    }


}
