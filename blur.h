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
    Q_INVOKABLE void screenShot();
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

private:
    QImage blurred(const QImage& image, const QRectF &rect, int radius, bool alphaOnly);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private:
    QQuickView *m_pCurrentView;
    QImage      m_image;
    QImage      m_sImage;


public slots:
    void on_windowChanged(QQuickWindow *);
};

#endif // BLUR_H
