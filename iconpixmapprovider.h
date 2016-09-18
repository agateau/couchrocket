#ifndef ICONPIXMAPPROVIDER_H
#define ICONPIXMAPPROVIDER_H

#include <QQuickImageProvider>

class IconPixmapProvider : public QQuickImageProvider
{
public:
    IconPixmapProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // ICONPIXMAPPROVIDER_H
