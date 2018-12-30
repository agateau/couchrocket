#include "launchermodel.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>

LauncherModel::LauncherModel(QObject *parent)
    : QAbstractListModel(parent)
    , mWatcher(new QFileSystemWatcher(this))
{
    connect(mWatcher, &QFileSystemWatcher::directoryChanged, this, &LauncherModel::readDir);
}

int LauncherModel::rowCount(const QModelIndex &index) const
{
    return index.parent().isValid() ? 0 : mFileNames.count();
}

QVariant LauncherModel::data(const QModelIndex &index, int role) const
{
    const Launcher *launcher = getLauncherAtRow(index.row());
    if (!launcher) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        return launcher->name();
    } else if (role == Qt::DecorationRole) {
        return launcher->iconUrl();
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
    if (!mPath.isEmpty()) {
        mWatcher->removePath(mPath);
    }
    mPath = path;
    mWatcher->addPath(mPath);
    readDir();
    pathChanged(mPath);
}

void LauncherModel::launch(int row) const
{
    const auto launcher = getLauncherAtRow(row);
    if (!launcher) {
        qCritical() << "No launcher for row" << row;
        return;
    }
    launcher->launch();
}

QVariantMap LauncherModel::get(int row) const
{
    const auto launcher = getLauncherAtRow(row);
    if (!launcher) {
        qCritical() << "No launcher for row" << row;
        return {};
    }
    return {
        {"display", launcher->name()},
        {"decoration", launcher->iconUrl()}
    };
}

const Launcher *LauncherModel::getLauncherAtRow(int row) const
{
    if (row < 0 || row >= mFileNames.count()) {
        return nullptr;
    }
    auto fileName = mFileNames.at(row);
    return mLauncherByFileName.at(fileName).get();
}

void LauncherModel::readDir()
{
    QDir dir(mPath);
    QFileInfoList lst = dir.entryInfoList({"*.desktop"}, QDir::Files | QDir::NoDotAndDotDot);
    beginResetModel();
    mFileNames.clear();
    Q_FOREACH(const QFileInfo &info, lst) {
        auto fileName = info.fileName();
        mFileNames << fileName;
        auto it = mLauncherByFileName.find(fileName);
        if (it == mLauncherByFileName.end()) {
            qDebug() << "Adding" << fileName;
            mLauncherByFileName[fileName] = std::make_unique<Launcher>(info.filePath());
        } else {
            qDebug() << "Refreshing" << fileName;
            it->second->refresh();
        }
    }
    endResetModel();
}
