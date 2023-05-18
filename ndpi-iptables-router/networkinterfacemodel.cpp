#include "networkinterfacemodel.h"

NetworkInterfaceModel::NetworkInterfaceModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_interfaces(QNetworkInterface::allInterfaces())  // Получаем список всех интерфейсов
{}

int NetworkInterfaceModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return m_interfaces.count();
}

QVariant NetworkInterfaceModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    const QNetworkInterface& iface = m_interfaces[index.row()];

    if (role == NameRole)
        return iface.name();

    return QVariant();
}

QHash<int, QByteArray> NetworkInterfaceModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";

    return roles;
}
