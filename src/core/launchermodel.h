#ifndef LAUNCHERMODEL_H
#define LAUNCHERMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QList>

#include <memory>
#include <map>

#include <launcher.h>

class QFileSystemWatcher;

class LauncherModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:
    LauncherModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &index = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QString path() const;
    void setPath(const QString &path);

    Q_INVOKABLE void launch(int row) const;

    Q_INVOKABLE QVariantMap get(int row) const;

Q_SIGNALS:
    void pathChanged(const QString &path);

private:
    QFileSystemWatcher *mWatcher;
    QString mPath;
    QStringList mFileNames;
    std::map<QString, std::unique_ptr<Launcher>> mLauncherByFileName;

    const Launcher *getLauncherAtRow(int row) const;

    void readDir();
};

#endif // LAUNCHERMODEL_H
