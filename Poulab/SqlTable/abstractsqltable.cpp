#include "abstractsqltable.h"
#include "dbmanager.h"

#include <QDebug>

AbstractSqlTable::AbstractSqlTable(DbManager* parentDb)
{
    m_tableModel = nullptr;
    m_listModel = nullptr;
    m_treeModel = nullptr;

    m_parentDb = parentDb;

    m_mainChild = "";
}

AbstractSqlTable::~AbstractSqlTable()
{
    this->cleanModels();
}

void AbstractSqlTable::cleanModels()
{
    if(m_tableModel != nullptr)
        delete m_tableModel;
    if(m_listModel != nullptr)
        delete m_listModel;
    if(m_treeModel != nullptr)
        delete m_treeModel;
}

void AbstractSqlTable::resetModels()
{
    if(m_tableModel == nullptr)
    {
        this->cleanModels();
        this->constructModels();
    }
    if(m_tableModel != nullptr)
        m_tableModel->reset();
    if(m_listModel != nullptr)
        m_listModel->reset();
    if(m_treeModel != nullptr)
        m_treeModel->reset();
}

AbstractSqlTableModel* AbstractSqlTable::getTableModel() const
{
    return m_tableModel;
}

AbstractSqlListModel *AbstractSqlTable::getListModel() const
{
    return m_listModel;
}

AbstractSqlTreeModel *AbstractSqlTable::getTreeModel() const
{
    return m_treeModel;
}



const QString &AbstractSqlTable::getTableName() const
{
    return m_tableName;
}

const QString &AbstractSqlTable::getMainChild() const
{
    return m_mainChild;
}


const QMap<QString, SqlField> &AbstractSqlTable::getFieldTypeList() const
{
    return m_fieldTypeList;
}


QString AbstractSqlTable::retrieveSorterField() const
{
    QMap<QString, SqlField>::const_iterator f;
    for(f = m_fieldTypeList.begin() ; f != m_fieldTypeList.end() ; ++f)
        if(f.value().type() == SQLFIELD_SORTER)
            return f.key();
    return QString();
}


const SqlField *AbstractSqlTable::getSqlField(const QString &fieldName) const
{
    QMap<QString, SqlField>::const_iterator f = m_fieldTypeList.find(fieldName);

    if(f != m_fieldTypeList.end())
        return &f.value();
    return nullptr;
}

QString AbstractSqlTable::getParentFieldName(const QString &parentName) const
{
    QMap<QString, SqlField>::const_iterator f;;
    for(f = m_fieldTypeList.begin() ; f != m_fieldTypeList.end() ; ++f)
        if(f.value().type() == SQLFIELD_LINK
         && f.value().linkName() == parentName)
            return f.key();

    return QString();
}

DbManager *AbstractSqlTable::getParentDb() const
{
    return m_parentDb;
}

void AbstractSqlTable::createNewTable()
{
    QSqlQuery query;

    QString query_txt =
            "CREATE TABLE "+m_tableName+" ( `ID` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE";

    QMap<QString,SqlField>::iterator i;
    for(i = m_fieldTypeList.begin() ; i != m_fieldTypeList.end() ; ++i)
    {
        query_txt += " , `"+i.key()+"` ";
        if(i.value().type() == SQLFIELD_TEXT) query_txt += "TEXT";
        else if(i.value().type() == SQLFIELD_REAL) query_txt += "REAL";
        else query_txt += "INTEGER";
    }
    query_txt += ");";

    query.exec(query_txt);
    qInfo()<<query.lastQuery();
}

void AbstractSqlTable::verifyTableIntegrity()
{
    QSqlQuery query;

    query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='"+m_tableName+"'");
    if(query.size() == 0)
        this->createNewTable();
    else
    {
        QList<QString> fieldNameList;
        query.exec("PRAGMA table_info("+m_tableName+")");
        while(query.next())
            fieldNameList.push_back(query.value(1).toString());

        QMap<QString,SqlField>::iterator i;
        for(i = m_fieldTypeList.begin() ; i != m_fieldTypeList.end() ; ++i)
            this->verifyFieldExistence(i.key(),i.value(), &fieldNameList);
    }
}

void AbstractSqlTable::verifyFieldExistence(const QString &fieldName, const SqlField &fieldType, const QList<QString> *fieldList)
{
    bool founded = false;
    QList<QString>::const_iterator i;
    for(i = fieldList->begin() ; i != fieldList->end() && !founded ; ++i)
        if(fieldName == *i)
            founded = true;

    if(!founded)
    {
        QSqlQuery query;
        QString query_txt = "ALTER TABLE "+m_tableName+" ADD "+fieldName+" ";

        if(fieldType.type() == SQLFIELD_TEXT) query_txt += "TEXT ;";
        else if(fieldType.type() == SQLFIELD_REAL) query_txt += "REAL ;";
        else query_txt += "INTEGER ;";

        query.exec(query_txt);
        qInfo()<<query.lastQuery();
    }
}

void AbstractSqlTable::readTable()
{
    this->readTable(QuickSqlQuery(m_tableName));
}

void AbstractSqlTable::readTable(const QuickSqlQuery &quickquery)
{
   m_data.clear();

   QString sorterField = this->retrieveSorterField();

   QSqlQuery query = quickquery.generateSelectQuery(sorterField);
   m_lastQuery = query.lastQuery();
   qInfo()<<m_lastQuery;

   while(query.next())
       m_data.push_back(SqlDatum(this,&query));

   this->resetModels();
}

void AbstractSqlTable::reReadTable()
{

}

SqlDatum AbstractSqlTable::getDatumFromID(int ID) const
{
    QSqlQuery query("SELECT * FROM "+m_tableName+" WHERE ID = "+QVariant(ID).toString()+";");
    query.next();

    qInfo()<<query.lastQuery();

    return SqlDatum(this,&query);
}

SqlDatum AbstractSqlTable::getFirstMatchDatum(const QString &filter) const
{
    return this->getFirstMatchDatum(QuickSqlQuery(m_tableName, filter));
}

SqlDatum AbstractSqlTable::getFirstMatchDatum(const QuickSqlQuery &quickquery) const
{
    QSqlQuery query = quickquery.generateSelectQuery();

    qInfo()<<query.lastQuery();

    if(query.next())
        return SqlDatum(this,&query);
    else
        return SqlDatum();
}



