#include "iconpixmapprovider.h"

#include <QDebug>
#include <QIcon>

IconPixmapProvider::IconPixmapProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap IconPixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QIcon icon = QIcon::fromTheme(id);
    if (icon.isNull()) {
        icon = QIcon::fromTheme("applications-system");
    }
    QPixmap pix = icon.pixmap(requestedSize);
    if (pix.size() != requestedSize) {
        pix = pix.scaled(requestedSize);
    }
    if (size) {
        *size = pix.size();
    }
    return pix;
}

