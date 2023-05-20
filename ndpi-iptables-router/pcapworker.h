#ifndef PCAPWORKER_H
#define PCAPWORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <pcap.h>
#include <ndpi/ndpi_main.h>

class PcapWorker : public QThread
{
    Q_OBJECT

public:
    explicit PcapWorker(QObject *parent = nullptr);
    ~PcapWorker();

public slots:
    void setFilename(QString fn)
    {
        this->filename = fn;
        qDebug() << "Filename changed";
    }
signals:
    void packetInfo(const QString &proto, const QString &srcIP,
                    const QString dstIP, const QString pcapProto);

protected:
    void run() override;

private:
    QString filename;
    struct ndpi_detection_module_struct *ndpi_struct;
};

#endif // PCAPWORKER_H
