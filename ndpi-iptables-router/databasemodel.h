#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QDebug>

class DatabaseModel : QSqlTableModel
{
    Q_OBJECT
public:
    explicit DatabaseModel(QObject *parent = NULL);

};

#endif // DATABASEMODEL_H
