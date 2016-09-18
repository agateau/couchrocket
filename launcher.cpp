#include "launcher.h"

#include <QProcess>
#include <QSettings>

Launcher::Launcher(const QString &desktopFilePath)
{
    QSettings settings(desktopFilePath, QSettings::IniFormat);
    settings.beginGroup("Desktop Entry");
    mName = settings.value("Name").toString();
    mIconUrl = QUrl("image://icon/" +  settings.value("Icon").toString());
    mExec = settings.value("Exec").toString();
    mExec.replace("%u", "");
    mExec.replace("%U", "");
    mExec.replace("%f", "");
    mExec.replace("%F", "");
}


QString Launcher::name() const
{
    return mName;
}
QUrl Launcher::iconUrl() const
{
    return mIconUrl;
}

void Launcher::launch() const
{
    QProcess::startDetached(mExec);
}
