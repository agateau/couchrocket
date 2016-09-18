# Config

Launchers stored in ~/.local/couchrocket/launchers

# UI

## main.qml

Contains a view and a LaunchItemModel

Contains UI to shutdown

# Core

## Launcher

Knows how to read a .desktop file

API:

    internalName ($app.desktop or of $dir/.directory)
    name
    icon
    launch()

## LauncherModel

Inherits from QAbstractListModel

Contains Launcher

API:

    setDir(const QString &)
