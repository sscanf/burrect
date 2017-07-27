#ifndef BLUR_H
#define BLUR_H

#include <QQuickItem>
#include <QPixmap>
#include <QQuickView>
#include <QString>

class blur : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(blur)

public:
    blur(QQuickItem *parent = nullptr);
    ~blur();
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);


private:
    QImage blurred(const QImage& image, const QRectF &rect, int radius, bool alphaOnly);
//    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private:
    QQuickView *m_pCurrentView;
    QImage      m_image;
    QImage      m_sImage;


public slots:
    void on_windowChanged(QQuickWindow *);
    void screenShot();
};

#endif // BLUR_H
