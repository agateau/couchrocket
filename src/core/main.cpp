#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <iconpixmapprovider.h>
#include <launchermodel.h>

static QString getDefaultLauncherDir()
{
    return QDir::home().filePath(".local/share/couchrocket/launchers");
}

static QVariantMap loadConfig()
{
    QSettings settings("couchrocket", "couchrocket");
    return {
        {"themeName", settings.value("iconTheme")},
        {"launcherDir", settings.value("launcherDir", getDefaultLauncherDir())},
        {"fullScreen", settings.value("fullScreen", false)},
    };
}

static void updateConfigFromArguments(QVariantMap* config, const QCoreApplication& app)
{
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
        {{"f", "fullscreen"}, QCoreApplication::translate("main", "Start in fullscreen mode.")},
    });
    parser.addPositionalArgument("launcherDir", QCoreApplication::translate("main", "Launcher dir"));
    parser.process(app);

    if (parser.isSet("fullscreen")) {
        (*config)["fullScreen"] = true;
    }

    QStringList posArgs = parser.positionalArguments();
    if (posArgs.length() == 1) {
        (*config)["launcherDir"] = posArgs[0];
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("Couch Rocket");
    app.setApplicationVersion("1.0.0");

    QVariantMap config = loadConfig();
    updateConfigFromArguments(&config, app);

    QString launcherDir = config["launcherDir"].toString();
    qDebug() << "launcherDir:" << launcherDir;
    if (!QFile::exists(launcherDir)) {
        qCritical() << "launcherDir does not exist";
        return 1;
    }

    QString themeName = config["themeName"].toString();
    if (!themeName.isEmpty()) {
        QIcon::setThemeName(themeName);
    }
    qDebug() << "theme:" << QIcon::themeName();

    QQmlApplicationEngine engine;
    qmlRegisterType<LauncherModel>("CouchRocket", 1, 0, "LauncherModel");
    engine.rootContext()->setContextProperty("config", config);
    engine.addImageProvider("icon", new IconPixmapProvider);
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}

