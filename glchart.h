#ifndef GLCHART_H
#define GLCHART_H

#include <QQuickItem>

class GLChart : public QQuickItem
{
    Q_OBJECT
public:
    GLChart(QQuickItem* parent = 0);

protected:
    QSGNode* updatePaintNode(QSGNode *oldNode,
                             UpdatePaintNodeData* data) override;
};

#endif // GLCHART_H
