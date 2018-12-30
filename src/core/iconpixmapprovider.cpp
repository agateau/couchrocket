#include "iconpixmapprovider.h"

#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QImageReader>
#include <QPainter>

static constexpr char BROKEN_IMAGE[] = ":/images/broken.svg";
static constexpr char DEFAULT_IMAGE[] = ":/images/rocket.svg";

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

static QPixmap loadPixmapFromPath(const QString &path, const QSize &requestedSize)
{
    if (!QFile::exists(path)) {
        return QPixmap();
    }
    QImageReader reader(path);
    if (!requestedSize.isEmpty()) {
        QSize size = reader.size().scaled(requestedSize, Qt::KeepAspectRatioByExpanding);
        reader.setScaledSize(size);
    }
    return QPixmap::fromImage(reader.read());
}

static QPixmap loadRawPixmap(const QString &id, const QSize &requestedSize)
{
    if (id.isEmpty()) {
        return loadPixmapFromPath(DEFAULT_IMAGE, requestedSize);
    }

    // Try to consider id as a full path
    QPixmap pix = loadPixmapFromPath(id, requestedSize);
    if (!pix.isNull()) {
        return pix;
    }

    // No luck, is it a theme icon?
    QIcon icon = QIcon::fromTheme(id);
    if (!icon.isNull()) {
        return icon.pixmap(qMax(requestedSize.width(), requestedSize.height()));
    }

    // Still no luck, look in the fallback dir
    QString dir = QString(FALLBACK_DIR) + '/';
    for (auto ext = FALLBACK_EXTS; *ext != 0; ++ext) {
        QString path = dir + id + *ext;
        QPixmap pix = loadPixmapFromPath(path, requestedSize);
        if (!pix.isNull()) {
            return pix;
        }
    }

    // This icon is broken
    return loadPixmapFromPath(BROKEN_IMAGE, requestedSize);
}

IconPixmapProvider::IconPixmapProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap IconPixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int extent = qMax(requestedSize.width(), requestedSize.height());
    const QString cacheId = QString("%1-%2").arg(id).arg(extent);

    QPixmap pix;
    {
        QMutexLocker lock(&mMutex);
        auto it = mCache.find(cacheId);
        if (it != mCache.end()) {
            pix = *it;
        }
    }
    if (pix.isNull()) {
        pix = loadRawPixmap(id, {extent, extent});
        QMutexLocker lock(&mMutex);
        mCache.insert(cacheId, pix);
    }

    if (!requestedSize.isEmpty() && pix.size() != requestedSize) {
        pix = scalePixmap(pix, requestedSize);
    }
    if (size) {
        *size = pix.size();
    }
    return pix;
}

