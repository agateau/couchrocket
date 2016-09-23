#include "iconpixmapprovider.h"

#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QPainter>

static constexpr char UNKNOWN_IMAGE[] = ":/images/broken.svg";

static constexpr char FALLBACK_DIR[] = "/usr/share/pixmaps";
static constexpr const char *FALLBACK_EXTS[] = {".svg", ".png", ".xpm", 0};

static QPixmap scalePixmap(const QPixmap &fg_, const QSize &size)
{
    QPixmap fg = fg_.scaled(size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap pix(size);
    pix.fill(Qt::transparent);
    QPainter painter(&pix);
    painter.drawPixmap(size.width() - fg.width(), size.height() - fg.height(), fg);
    return pix;
}

static QPixmap loadRawPixmap(const QString &id, const QSize &requestedSize)
{
    if (QFile::exists(id)) {
        QPixmap pix = QPixmap(id);
        if (!pix.isNull()) {
            return pix;
        }
    }

    QIcon icon = QIcon::fromTheme(id);
    if (!icon.isNull()) {
        return icon.pixmap(requestedSize);
    }

    QString dir = QString(FALLBACK_DIR) + '/';
    for (auto ext = FALLBACK_EXTS; *ext != 0; ++ext) {
        QString path = dir + id + *ext;
        QPixmap pix(path);
        if (!pix.isNull()) {
            return pix;
        }
    }

    return QPixmap(UNKNOWN_IMAGE);
}

IconPixmapProvider::IconPixmapProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap IconPixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QPixmap pix = loadRawPixmap(id, requestedSize);

    if (pix.size() != requestedSize) {
        pix = scalePixmap(pix, requestedSize);
    }
    if (size) {
        *size = pix.size();
    }
    return pix;
}

