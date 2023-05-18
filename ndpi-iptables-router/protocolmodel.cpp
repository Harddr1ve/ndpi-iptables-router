#include "protocolmodel.h"

ProtocolModel::ProtocolModel(QObject *parent) : QAbstractTableModel(parent)
{}

int ProtocolModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}
int ProtocolModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}
QVariant ProtocolModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_data.count())
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return m_data.at(index.row()).first;
        case 1:
            return m_data.at(index.row()).second;
        }
    }

    return QVariant();
}
void ProtocolModel::addRow(const QString &col1Data, const QString &col2Data) {
    beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
    m_data.append(qMakePair(col1Data, col2Data));
    endInsertRows();
}
