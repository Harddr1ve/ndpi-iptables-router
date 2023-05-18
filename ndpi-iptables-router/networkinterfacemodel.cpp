#include "networkinterfacemodel.h"

NetworkInterfaceModel::NetworkInterfaceModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_interfaces(QNetworkInterface::allInterfaces()){}
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
void NetworkInterfaceModel::handleModelItem(QVariant item) {
    bool ok;
    int index = item.toInt(&ok);
    if(ok) {
        QVariant data = this->data(this->index(index), NameRole);
        qDebug() << "Received item data: " << data.toString();
        emit selectedInterface(data.toString());
    }
}
