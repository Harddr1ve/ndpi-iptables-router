#ifndef NETWORKINTERFACEMODEL_H
#define NETWORKINTERFACEMODEL_H

#include <QAbstractListModel>
#include <QNetworkInterface>

class NetworkInterfaceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
    };

    NetworkInterfaceModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;


signals:
    void selectedInterface(const QString interface);
public slots:
    void handleModelItem(QVariant item) {
        bool ok;
        int index = item.toInt(&ok);
        if(ok) {
            QVariant data = this->data(this->index(index), NameRole);
            qDebug() << "Received item data: " << data.toString();
            emit selectedInterface(data.toString());
        }
    }

private:
    QList<QNetworkInterface> m_interfaces;
};


#endif // NETWORKINTERFACEMODEL_H
