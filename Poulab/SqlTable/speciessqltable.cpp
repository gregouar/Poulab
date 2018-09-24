#include "speciessqltable.h"
#include "TableModel/speciestablemodel.h"
#include "ListModel/specieslistmodel.h"

SpeciesSqlTable::SpeciesSqlTable(DbManager* parentDb) :
    AbstractSqlTable(parentDb)
{
    m_tableName = "Species";
    m_mainChild = "Individual";

    m_fieldTypeList.insert("Name",SqlField (SQLFIELD_TEXT,true));
    m_fieldTypeList.insert("Genus",SqlField (SQLFIELD_TEXT,true));
    m_fieldTypeList.insert("Subfamily",SqlField (SQLFIELD_TEXT,false));
    m_fieldTypeList.insert("Family",SqlField (SQLFIELD_TEXT,false));
    m_fieldTypeList.insert("Clade",SqlField (SQLFIELD_TEXT,true));
}

void SpeciesSqlTable::constructModels()
{
    m_tableModel = new SpeciesTableModel(&m_data);
    m_listModel = new SpeciesListModel(&m_data);
}



