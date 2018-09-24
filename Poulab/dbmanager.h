/** This big guy take care of making the connexion with the database.
 * You need to implement its constructor to tell him the tables you want in the db.
 * It will then take care of constructing them or verify they are like you want.
**/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDir>
#include <QList>

#include "SqlDatum/quicksqlquery.h"
#include "SqlTable/abstractsqltable.h"
#include "ListModel/abstractsqllistmodel.h"
#include "TreeModel/abstractsqltreemodel.h"

class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(QObject *parent = nullptr);
    ~DbManager();

    bool executeQuery(const QString &text);

    QAbstractTableModel* getTableModel(const QuickSqlQuery &quickquery);
    AbstractSqlListModel *getListModel(const QuickSqlQuery &quickquery);
    AbstractSqlTreeModel *getTreeModel(const QuickSqlQuery &quickquery);
    SqlDatum getDatumFromId(const QString &tableName, const int ID) const;
    SqlDatum getFirstMatchDatum(const QString &tableName, const QString &filter = "") const;
    SqlDatum getFirstMatchDatum(const QuickSqlQuery &quickquery) const;
    const AbstractSqlTable* getTable(const QString &tableName) const;
    int count(const QString &tablename) const;
    int count(const QuickSqlQuery &quickquery) const;

    QString searchParentLinkFieldName(const QString &curTableName, const QString &parentTableName) const;

    QString getItemListName(const QString &tableName, int ID);

    const QString &getFilePath();
    QDir getDirectory();

    QList<QString> getTableNameList() const;
    const QList<AbstractSqlTable*> getTableList() const;

protected:
    void verifyDatabaseIntegrity();

signals:
    void connected(bool);

public slots:
    void createDb();
    void createDb(const QString &dbName);
    void openDb();
    void saveDbAs();
    void closeDb();
    void connectToDb(const QString &dbName);

    void readTable(const QuickSqlQuery &q);

private:
    void createAllNewTables();
    AbstractSqlTable* getNonConstTable(const QString &tableName);

    QSqlDatabase m_db;
    QString m_dbFilePath;

    QMap<QString, AbstractSqlTable*> m_tablesList;
};

#endif // DBMANAGER_H
