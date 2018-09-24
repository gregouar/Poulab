#include "sqldatum.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

#include "SqlTable/abstractsqltable.h"


SqlDatum::SqlDatum(const AbstractSqlTable* parentTable, const int ID)
{
    m_ID = ID;
    m_parentTable = parentTable;
}


SqlDatum::SqlDatum(const AbstractSqlTable* parentTable, const QSqlQuery *query) :
     SqlDatum(parentTable, query->value(query->record().indexOf("ID")).toInt())
{
    QMap<QString, SqlField>::const_iterator i;
    for(i = m_parentTable->getFieldTypeList().begin() ; i != m_parentTable->getFieldTypeList().end() ; ++i)
       m_fieldValueList[&i.value()] = query->value(query->record().indexOf(i.key()));
}


SqlDatum::~SqlDatum()
{

}

bool SqlDatum::isValid() const
{
    return (m_parentTable != nullptr);
}

bool SqlDatum::isChildOf(const SqlField* parentingField, int ID) const
{
    if(this->getID() == ID)
        return true;

    int parentID = -1;

    QMap<const SqlField*, QVariant>::const_iterator f = m_fieldValueList.find(parentingField);
    if(f != m_fieldValueList.end())
        parentID = f.value().toInt();

    if(parentID == -1)
        return false;
    else if(parentID == ID)
        return true;
    else
        return m_parentTable->getDatumFromID(parentID).isChildOf(parentingField, ID);
}


int SqlDatum::getID() const
{
    return m_ID;
}

const AbstractSqlTable *SqlDatum::getParentTable() const
{
    return m_parentTable;
}

void SqlDatum::addToTable() const
{
    this->addToTableAs(this->getID());
}

void SqlDatum::addToTableAs(int target_id) const
{
    QSqlQuery query;
    QMap<QString, SqlField>::const_iterator i;

    if(target_id == -1)
    {
        QString query_txt = "INSERT INTO "+m_parentTable->getTableName()+"(`ID`";

        for(i = m_parentTable->getFieldTypeList().begin() ; i != m_parentTable->getFieldTypeList().end() ; ++i)
            query_txt += ",`"+i.key()+"`";

        query_txt += ") VALUES (NULL";


        for(i = m_parentTable->getFieldTypeList().begin() ; i != m_parentTable->getFieldTypeList().end() ; ++i)
        {
            if(i.value().type() == SQLFIELD_TEXT)
                query_txt += ",'"+m_fieldValueList[&i.value()].toString()+"'";
            else
            {
                QString value = m_fieldValueList[&i.value()].toString();
                if(value.isEmpty())
                    value = "-1";
                query_txt += ","+value+"";
            }
        }

        query_txt += ");";

        query.exec(query_txt);
    } else {
        QString query_txt = "UPDATE "+m_parentTable->getTableName()+" SET ";

        for(i = m_parentTable->getFieldTypeList().begin() ; i != m_parentTable->getFieldTypeList().end() ; ++i)
        {
            if(i != m_parentTable->getFieldTypeList().begin())
                query_txt += " , ";
            query_txt += i.key() + " = ";

            if(i.value().type() == SQLFIELD_TEXT)
                query_txt += "'"+m_fieldValueList[&i.value()].toString()+"'";
            else
                query_txt += m_fieldValueList[&i.value()].toString();
        }

        query_txt += " WHERE ID = "+QVariant(target_id).toString()+";";

        query.exec(query_txt);
    }

    qInfo()<<query.lastQuery();
}

void SqlDatum::deleteFromTable() const
{
    QSqlQuery query;
    query.exec("DELETE FROM "+m_parentTable->getTableName()+" WHERE ID="+QVariant(m_ID).toString()+";");
}


QVariant SqlDatum::getFieldValue(const QString &fieldName) const
{
    if(!isValid())
        return QVariant();

    const SqlField *f = m_parentTable->getSqlField(fieldName);
    if(f != nullptr)
        return m_fieldValueList[f];
    return QVariant();
}

void SqlDatum::setFieldValue(const QString &fieldName, const QVariant &value)
{
    if(isValid())
    {
        const SqlField *f = m_parentTable->getSqlField(fieldName);
        if(f != nullptr)
            m_fieldValueList[f] = value;
    }
}




