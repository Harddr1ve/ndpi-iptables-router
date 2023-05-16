#ifndef PROTOCOLMODEL_H
#define PROTOCOLMODEL_H

#include <QAbstractTableModel>

class ProtocolModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    explicit ProtocolModel(QObject *parent = nullptr);
    enum Roles {
        NameRole = Qt::UserRole + 1,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    QHash<int, QByteArray> roleNames() const override
//    {
//        return { {Qt::DisplayRole, "display"}};
//    }
};

#endif // PROTOCOLMODEL_H
