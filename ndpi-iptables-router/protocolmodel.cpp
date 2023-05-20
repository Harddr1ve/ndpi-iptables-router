#include "protocolmodel.h"

ProtocolModel::ProtocolModel(QObject *parent) : QAbstractTableModel(parent)
{}

int ProtocolModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_pcapData.count();
}
int ProtocolModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 4;
}
QVariant ProtocolModel::data(const QModelIndex &index, int role) const {

    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return m_pcapData.at(index.row()).proto;
        case 1:
            return m_pcapData.at(index.row()).srcIp;
        case 2:
            return m_pcapData.at(index.row()).dstIP;
        case 3:
            return m_pcapData.at(index.row()).pcapProto;
        }
    }

    return QVariant();
}
void ProtocolModel::addRow(const QString &col1Data, const QString &col2Data) {
    beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
    m_data.append(qMakePair(col1Data, col2Data));
    endInsertRows();
}

void ProtocolModel::addPcapRow(const QString &proto, const QString &srcIP, const QString dstIP, const QString pcapProto)
{
    beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
    p_pcapData = {proto,srcIP,dstIP, pcapProto};
    m_pcapData.append(p_pcapData);
    endInsertRows();
}
