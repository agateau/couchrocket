#ifndef LAUNCHERMODEL_H
#define LAUNCHERMODEL_H

#include <QAbstractListModel>
#include <QList>

#include <launcher.h>

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
    QString mPath;
    QList<Launcher> mLaunchers;

    void readDir();
};

#endif // LAUNCHERMODEL_H
