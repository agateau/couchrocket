TEMPLATE = app

QT += qml quick quickcontrols2
CONFIG += c++11

SOURCES += main.cpp \
    launchermodel.cpp \
    launcher.cpp \
    iconpixmapprovider.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    launchermodel.h \
    launcher.h \
    iconpixmapprovider.h

