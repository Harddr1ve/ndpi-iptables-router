#ifndef PROTOCOLMODEL_H
#define PROTOCOLMODEL_H

#include <QAbstractTableModel>
#include <QDebug>
#include <QString>

class ProtocolModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    explicit ProtocolModel(QObject *parent = nullptr);
    enum Roles {
        NameRole = Qt::UserRole + 1,
    };
    struct PcapData
    {
        QString proto;
        QString srcIp;
        QString dstIP;
        QString pcapProto;
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void addRow(const QString &col1Data, const QString &col2Data);
    void addPcapRow(const QString &proto, const QString &srcIP,
                    const QString dstIP, const QString pcapProto);

private:
    QList<QPair<QString, QString>> m_data;
    QList<PcapData> m_pcapData;
    PcapData p_pcapData;

};

#endif // PROTOCOLMODEL_H
