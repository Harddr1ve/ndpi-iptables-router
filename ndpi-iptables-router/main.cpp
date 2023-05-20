#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QString>
#include <QProcess>
#include <pcap.h>
#include <ndpi/ndpi_api.h>

#include "protocolmodel.h"
#include "networkinterfacemodel.h"
#include "dpiworker.h"
#include "pcapworker.h"
#include "commandrunner.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DPIWorker worker;
    PcapWorker pcapWorker;
    CommandRunner commandRunner;
    NetworkInterfaceModel networkInterfaceModel;
    ProtocolModel protocolModel;

    QObject::connect(&networkInterfaceModel, &NetworkInterfaceModel::selectedInterface, &worker, &DPIWorker::updateInterface);
    QObject::connect(&worker, &DPIWorker::packetProcessed, &protocolModel, &ProtocolModel::addRow);
    QObject::connect(&pcapWorker, &PcapWorker::packetInfo, &protocolModel, &ProtocolModel::addPcapRow);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("worker", &worker);
    engine.rootContext()->setContextProperty("pcapWorker", &pcapWorker);
    engine.rootContext()->setContextProperty("commandRunner", &commandRunner);
    engine.rootContext()->setContextProperty("networkInterfaceModel", &networkInterfaceModel);
    engine.rootContext()->setContextProperty("protocolModel", &protocolModel);
    const QUrl url(u"qrc:/ndpi-iptables-router/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
