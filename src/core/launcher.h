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

    void refresh();

private:
    const QString mDesktopFilePath;
    QString mName;
    QUrl mIconUrl;
    QString mExec;
};

#endif // LAUNCHER_H
