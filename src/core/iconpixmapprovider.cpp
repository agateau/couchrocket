#include "iconpixmapprovider.h"

#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QPainter>

static QPixmap scalePix(const QPixmap &fg_, const QSize &size)
{
    QPixmap fg = fg_.scaled(size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap pix(size);
    pix.fill(Qt::transparent);
    QPainter painter(&pix);
    painter.drawPixmap(size.width() - fg.width(), size.height() - fg.height(), fg);
    return pix;
}

IconPixmapProvider::IconPixmapProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap IconPixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QPixmap pix;
    if (QFile::exists(id)) {
        pix.load(id);
    } else {
        QIcon icon = QIcon::fromTheme(id);
        if (icon.isNull()) {
            icon = QIcon::fromTheme("applications-system");
        }
        pix = icon.pixmap(requestedSize);
    }
    if (pix.isNull()) {
        pix.load(":/images/rocket.svg");
    }

    if (pix.size() != requestedSize) {
        pix = scalePix(pix, requestedSize);
    }
    if (size) {
        *size = pix.size();
    }
    return pix;
}

