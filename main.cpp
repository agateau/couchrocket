#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <iconpixmapprovider.h>
#include <launchermodel.h>

static QString getDefaultLauncherDir()
{
    return QDir::home().filePath(".local/share/couchrocket/launchers");
}

QVariantMap parseArguments(const QCoreApplication& app)
{
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
        {{"f", "fullscreen"}, QCoreApplication::translate("main", "Start in fullscreen mode.")},
    });
    parser.addPositionalArgument("launcherDir", QCoreApplication::translate("main", "Launcher dir"));
    parser.process(app);

    QStringList posArgs = parser.positionalArguments();

    QString launcherDir;
    if (posArgs.length() == 1) {
        launcherDir = posArgs[0];
    } else {
        launcherDir = getDefaultLauncherDir();
    }

    return {
        {"fullScreen", parser.isSet("fullscreen")},
        {"launcherDir", launcherDir}
    };
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("Couch Rocket");
    app.setApplicationVersion("1.0.0");

    QVariantMap args = parseArguments(app);

    QString launcherDir = args["launcherDir"].toString();
    qDebug() << "launcherDir:" << launcherDir;
    if (!QFile::exists(launcherDir)) {
        qCritical() << "launcherDir does not exist";
        return 1;
    }

    QQmlApplicationEngine engine;
    qmlRegisterType<LauncherModel>("CouchRocket", 1, 0, "LauncherModel");
    engine.rootContext()->setContextProperty("config", args);
    engine.addImageProvider("icon", new IconPixmapProvider);
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}

