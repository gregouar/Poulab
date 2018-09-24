/** An SqlDatum contains the data of a record in a table. **/

#ifndef SQLDATUM_H
#define SQLDATUM_H

#include <QObject>
#include <QSqlQuery>
#include <QMap>

#include "SqlDatum/sqlfield.h"

class AbstractSqlTable;

class SqlDatum
{
public:
    SqlDatum(const AbstractSqlTable* parentTable = nullptr, const int ID = -1);
    SqlDatum(const AbstractSqlTable* parentTable, const QSqlQuery *query);
    virtual ~SqlDatum();

    void addToTable() const;
    void addToTableAs(int id) const;
    void deleteFromTable() const;

    bool isValid() const;
    bool isChildOf(const SqlField *parentingField, int ID) const;

    int getID() const;
    const AbstractSqlTable *getParentTable() const;
    QVariant getFieldValue(const QString &) const;

    void setFieldValue(const QString &, const QVariant &);

protected:
    int m_ID;

    const AbstractSqlTable *m_parentTable;
    QMap<const SqlField*, QVariant> m_fieldValueList;
};

#endif // SQLDATUM_H
