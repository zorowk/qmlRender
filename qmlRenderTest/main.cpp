#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include <QStringLiteral>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QLoggingCategory::setFilterRules(QStringLiteral("qt.scenegraph.general=true"));
    qSetMessagePattern("%{category}: %{message}");

    QQmlApplicationEngine engine;
    const QUrl url(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                      &app, [url](QObject *obj, const QUrl &objUrl) {
         if (!obj && url == objUrl)
             QCoreApplication::exit(-1);
     }, Qt::QueuedConnection);
    engine.load(url);
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
