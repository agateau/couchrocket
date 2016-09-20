#include "launchermodel.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>

LauncherModel::LauncherModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int LauncherModel::rowCount(const QModelIndex &index) const
{
    return index.parent().isValid() ? 0 : mLaunchers.count();
}

QVariant LauncherModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= mLaunchers.count()) {
        return QVariant();
    }
    const Launcher& launcher = mLaunchers.at(row);
    if (role == Qt::DisplayRole) {
        return launcher.name();
    } else if (role == Qt::DecorationRole) {
        return launcher.iconUrl();
    } else {
        return QVariant();
    }
}

QString LauncherModel::path() const
{
    return mPath;
}

void LauncherModel::setPath(const QString &path)
{
    if (mPath == path) {
        return;
    }
    mPath = path;
    readDir();
    pathChanged(mPath);
}

void LauncherModel::launch(int row) const
{
    Q_ASSERT(row >= 0 && row < mLaunchers.count());
    mLaunchers.at(row).launch();
}

QVariantMap LauncherModel::get(int row) const
{
    Q_ASSERT(row >= 0 && row < mLaunchers.count());
    const Launcher& launcher = mLaunchers.at(row);
    QVariantMap hash;
    hash["display"] = launcher.name();
    hash["decoration"] = launcher.iconUrl();
    return hash;
}

void LauncherModel::readDir()
{
    QDir dir(mPath);
    QFileInfoList lst = dir.entryInfoList({"*.desktop"}, QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    beginResetModel();
    mLaunchers.clear();
    Q_FOREACH(const QFileInfo &info, lst) {
        Launcher launcher(info.absoluteFilePath());
        mLaunchers << launcher;
    }
    endResetModel();
}
