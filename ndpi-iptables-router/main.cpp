#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QString>
#include <QCommandLineOption>
#include <QProcess>
#include <pcap.h>
#include <ndpi/ndpi_api.h>

#include "protocolmodel.h"
#include "networkinterfacemodel.h"
#include "dpiworker.h"
#include "commandrunner.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DPIWorker worker;
    CommandRunner commandRunner;
    NetworkInterfaceModel networkInterfaceModel;

    QObject::connect(&networkInterfaceModel, &NetworkInterfaceModel::selectedInterface, &worker, &DPIWorker::updateInterface);

    qmlRegisterType<NetworkInterfaceModel>("com.example", 1, 0, "NetworkInterfaceModel");
    qmlRegisterType<ProtocolModel>("ProtocolModel", 1, 0, "ProtocolModel");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("worker", &worker);
    engine.rootContext()->setContextProperty("commandRunner", &commandRunner);
    engine.rootContext()->setContextProperty("networkInterfaceModel", &networkInterfaceModel);
    const QUrl url(u"qrc:/ndpi-iptables-router/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
