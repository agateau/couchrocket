#ifndef ICONPIXMAPPROVIDER_H
#define ICONPIXMAPPROVIDER_H

#include <QQuickImageProvider>

#include <QMutex>
#include <QHash>

class IconPixmapProvider : public QQuickImageProvider
{
public:
    IconPixmapProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    QMutex mMutex;
    QHash<QString, QPixmap> mCache;
};

#endif // ICONPIXMAPPROVIDER_H
