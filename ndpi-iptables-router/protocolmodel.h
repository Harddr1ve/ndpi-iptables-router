#ifndef PROTOCOLMODEL_H
#define PROTOCOLMODEL_H

#include <QAbstractTableModel>
#include <QDebug>

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

public slots:
    void addRow(const QString &col1Data, const QString &col2Data);

private:
    QList<QPair<QString, QString>> m_data;

};

#endif // PROTOCOLMODEL_H
