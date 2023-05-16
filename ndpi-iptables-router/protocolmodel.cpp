#include "protocolmodel.h"

ProtocolModel::ProtocolModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int ProtocolModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 50;
}

int ProtocolModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant ProtocolModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column() + 1);
    }
    return QVariant();
}
