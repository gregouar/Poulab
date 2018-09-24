#include "museumsqltable.h"

#include "TableModel/museumtablemodel.h"
#include "ListModel/museumlistmodel.h"


MuseumSqlTable::MuseumSqlTable(DbManager* parentDb) :
    AbstractSqlTable(parentDb)
{
    m_tableName = "Museum";
    m_mainChild = "Individual";

    m_fieldTypeList.insert("Name",SqlField (SQLFIELD_TEXT,true));
    m_fieldTypeList.insert("Country",SqlField (SQLFIELD_TEXT,true));
}

void MuseumSqlTable::createNewTable()
{
    AbstractSqlTable::createNewTable();

    SqlDatum d(this);
    d.setFieldValue("Name","No museum");
    d.setFieldValue("Country","");
    d.addToTable();
}

void MuseumSqlTable::constructModels()
{
    m_tableModel = new MuseumTableModel(&m_data);
    m_listModel = new MuseumListModel(&m_data);
}




