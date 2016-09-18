#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QUrl>

class Launcher
{
public:
    Launcher(const QString &desktopFilePath);

    QString name() const;

    QUrl iconUrl() const;

    void launch() const;

private:
    QString mName;
    QUrl mIconUrl;
    QString mExec;
};

#endif // LAUNCHER_H
