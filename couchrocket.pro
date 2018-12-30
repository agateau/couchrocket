TEMPLATE = app

QT += qml quick quickcontrols2
CONFIG += c++14

SOURCES += src/core/main.cpp \
    src/core/launchermodel.cpp \
    src/core/launcher.cpp \
    src/core/iconpixmapprovider.cpp \

INCLUDEPATH += src/core

RESOURCES += src/ui/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = src/ui

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/core/launchermodel.h \
    src/core/launcher.h \
    src/core/iconpixmapprovider.h \

