#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "networkinterfacemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<NetworkInterfaceModel>("com.example", 1, 0, "NetworkInterfaceModel");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ndpi-iptables-router/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
