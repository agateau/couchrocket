#include "launcher.h"

#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QTextStream>

static constexpr char DESKTOP_ENTRY_GROUP[] = "[Desktop Entry]";

static QHash<QString, QString> readDesktopFile(QIODevice *device)
{
    QTextStream stream(device);
    QHash<QString, QString> hash;
    bool inDesktopEntryGroup = false;
    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        // Skip empty lines and comments
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        if (inDesktopEntryGroup) {
            if (line.at(0) == '[') {
                // We reached the beginning of a new group
                break;
            }
            int idx = line.indexOf('=');
            if (idx == -1) {
                qWarning() << "Invalid line" << line;
                continue;
            }
            QString key = line.left(idx).trimmed();
            QString value = line.mid(idx + 1).trimmed();
            hash[key] = value;
        } else {
            if (line == DESKTOP_ENTRY_GROUP) {
                inDesktopEntryGroup = true;
            }
        }
    }
    return hash;
}

Launcher::Launcher(const QString &desktopFilePath)
{
    QHash<QString, QString> hash;
    {
        QFile file(desktopFilePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Cannot read" << desktopFilePath;
            return;
        }
        hash = readDesktopFile(&file);
        if (hash.isEmpty()) {
            qWarning() << desktopFilePath << "contains no .desktop entries";
            return;
        }
    }

    mName = hash.value("Name");
    mIconUrl = QUrl("image://icon/" + hash.value("Icon"));
    mExec = hash.value("Exec");
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
    qDebug() << "Launching" << mExec;
    QProcess::startDetached(mExec);
}
