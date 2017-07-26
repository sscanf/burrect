#include "blur.h"
#include <QSGSimpleTextureNode>
#include <QSGTexture>
#include <QDebug>

blur::blur(QQuickItem *parent):
    QQuickItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    setFlag(ItemHasContents, true);
    connect (this, SIGNAL (windowChanged(QQuickWindow *)), this, SLOT (on_windowChanged(QQuickWindow *)));
}

QImage blur::blurred(const QImage& image, const QRectF& rect, int radius, bool  alphaOnly)
{
    int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
    int alpha = (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius-1];

    QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    int r1 = rect.top();
    int r2 = rect.bottom();
    int c1 = rect.left();
    int c2 = rect.right();

    int bpl = result.bytesPerLine();
    int rgba[4];
    unsigned char* p;

    int i1 = 0;
    int i2 = 3;

    if (alphaOnly)
    i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

    for (int col = c1; col <= c2; col++) {
        p = result.scanLine(r1) + col * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p += bpl;
        for (int j = r1; j < r2; j++, p += bpl)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = result.scanLine(row) + c1 * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p += 4;
        for (int j = c1; j < c2; j++, p += 4)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int col = c1; col <= c2; col++) {
        p = result.scanLine(r2) + col * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p -= bpl;
    for (int j = r1; j < r2; j++, p -= bpl)
        for (int i = i1; i <= i2; i++)
            p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = result.scanLine(row) + c2 * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p -= 4;
        for (int j = c1; j < c2; j++, p -= 4)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    return result;
}

void blur::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_sImage  = m_image.copy (newGeometry.x(), newGeometry.y(), newGeometry.width(), newGeometry.height());
    qDebug() << newGeometry.x() << newGeometry.y() << newGeometry.width() << newGeometry.height();
    update();
}

void blur::on_windowChanged(QQuickWindow *pWindow)
{
    if (pWindow) {
        m_sImage = QImage (pWindow->size(), QImage::Format_ARGB32);
        m_sImage.fill (Qt::transparent);
    }
}

blur::~blur()
{
}

void blur::screenShot()
{
    QImage image = window()->grabWindow();
    m_image = blurred (image,QRect (0,0,window()->width(),window()->height()),30,false);
    m_image.save ("/tmp/oscar.jpg");
    m_sImage  = m_image.copy (this->x(),this->y(),this->width(),this->height());
    this->update();
}

QSGNode *blur::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);
    qDebug() << node;
    if (!node) {
        node = new QSGSimpleTextureNode();
    }
    QSGTexture *texture = window()->createTextureFromImage(m_sImage);
    node->setTexture(texture);
    node->setRect(boundingRect());
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}
