#ifndef DPIWORKER_H
#define DPIWORKER_H

#include <QThread>
#include <QDebug>
#include <pcap.h>
#include <ndpi/ndpi_api.h> // include the nDPI library

#define MAX_PACKET_SIZE 65536

class DPIWorker : public QThread
{
    Q_OBJECT

public:
    explicit DPIWorker(QObject *parent = nullptr);
    ~DPIWorker();

public slots:
    void stop()
    {
        requestInterruption();
    }

    void updateInterface(QString interface)
    {
        s_interface = interface;
    }

signals:
    void packetProcessed(QString info, QString data);

private:
    QString s_interface;
    QString filename;
    struct ndpi_detection_module_struct *ndpi_struct;

protected:
    void run() override;
};

#endif // DPIWORKER_H
