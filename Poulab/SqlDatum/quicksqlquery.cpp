#include "quicksqlquery.h"

#include "dbmanager.h"

QuickSqlQuery::QuickSqlQuery(const QString &tableName,
                              const QString &filter,
                              const QString &with,
                             const QString &join)
{
    m_tableName = tableName;
    m_whereFilter = filter;
    m_with = with;
    m_join = join;
}

QSqlQuery QuickSqlQuery::generateSelectQuery(const QString &sorterField) const
{
    return generateQuery(sorterField);
}

QSqlQuery QuickSqlQuery::generateCountQuery(const QString &sorterField) const
{
    return generateQuery(sorterField,true);
}


QSqlQuery QuickSqlQuery::generateQuery(const QString &sorterField, bool count) const
{
    QString query_txt;

    if(!m_with.isEmpty())
        query_txt += " WITH " + m_with + " ";

    query_txt += "SELECT";
    query_txt += count ? " count(*) " : " * ";
    query_txt+= "FROM "+m_tableName;

    if(!m_join.isEmpty())
        query_txt += m_join;

    if(!m_whereFilter.isEmpty())
        query_txt += " WHERE " + m_whereFilter;

    if(!sorterField.isEmpty())
        query_txt += " ORDER BY "+sorterField+" ASC";

    query_txt += ";";

    QSqlQuery query(query_txt);

    return query;
}

const QString &QuickSqlQuery::tableName() const
{
    return m_tableName;
}
