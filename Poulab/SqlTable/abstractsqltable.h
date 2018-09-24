/** An AbstractSqlTable represent a table in the database. You need to inherit one per table you want in the database.
 * Then you need to insert columns as fields in m_fieldTypeList in the constructor.
  * Each inherited SqlTable should also have its correspoding Table model (for SearchWidget)
  * and List model (for ComboBox).
**/

#ifndef ABSTRACTSQLTABLE_H
#define ABSTRACTSQLTABLE_H

#include <QAbstractTableModel>

#include "SqlDatum/sqldatum.h"
#include "SqlDatum/sqlfield.h"
#include "SqlDatum/quicksqlquery.h"
#include "TableModel/abstractsqltablemodel.h"
#include "ListModel/abstractsqllistmodel.h"
#include "TreeModel/abstractsqltreemodel.h"

class DbManager;

class AbstractSqlTable
{
public:
    AbstractSqlTable(DbManager* parentDb);
    virtual ~AbstractSqlTable();

    virtual void createNewTable();
    virtual void readTable();
    virtual void readTable(const QuickSqlQuery &q);
    virtual void reReadTable();
    virtual SqlDatum getDatumFromID(int ID) const;
    virtual SqlDatum getFirstMatchDatum(const QString &filter = "") const;
    virtual SqlDatum getFirstMatchDatum(const QuickSqlQuery &q) const;

    virtual void constructModels() = 0;
    virtual void cleanModels();
    virtual void resetModels();

    AbstractSqlTableModel *getTableModel() const;
    AbstractSqlListModel *getListModel() const;
    AbstractSqlTreeModel *getTreeModel() const;
    const QString &getTableName() const;
    const QString &getMainChild() const;

    QString retrieveSorterField() const;
    const QMap<QString, SqlField> &getFieldTypeList() const;

    const SqlField *getSqlField(const QString &) const;
    QString getParentFieldName(const QString &parentName) const;
    DbManager *getParentDb() const;

    void verifyTableIntegrity();

private:
    void verifyFieldExistence(const QString &fieldName, const SqlField &fieldType, const QList<QString> *fieldList);

protected:
    QList<SqlDatum> m_data;
    QString m_lastQuery;

    DbManager* m_parentDb;

    QString m_tableName;
    QString m_mainChild;
    QMap<QString, SqlField> m_fieldTypeList;
    AbstractSqlTableModel *m_tableModel;
    AbstractSqlListModel *m_listModel;
    AbstractSqlTreeModel *m_treeModel;

};

#endif // ABSTRACTSQLTABLE_H
