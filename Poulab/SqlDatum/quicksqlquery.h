
#ifndef QUICKSQLQUERY_H
#define QUICKSQLQUERY_H

#include <QList>
#include <QString>
#include <QSqlQuery>

class DbManager;

class QuickSqlQuery
{
public:
    QuickSqlQuery(const QString &tableName,
                  const QString &filter = "",
                  const QString &with = "",
                  const QString &join = "");

    QSqlQuery generateSelectQuery(const QString &sorterField = "") const;
    QSqlQuery generateCountQuery(const QString &sorterField = "") const;

    const QString &tableName() const;

protected:
    QSqlQuery generateQuery(const QString &sorterField = "",bool count = false) const;

private:
    QString m_tableName;
    QString m_whereFilter;
    QString m_with;
    QString m_join;
};

#endif // QUICKSQLQUERY_H
