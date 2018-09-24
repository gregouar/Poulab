#include "materialsqltable.h"
#include "TableModel/materialtablemodel.h"
#include "ListModel/materiallistmodel.h"

MaterialSqlTable::MaterialSqlTable(DbManager* parentDb) :
    AbstractSqlTable(parentDb)
{
    m_tableName = "Material";
    m_mainChild = "Measurement";

    m_fieldTypeList.insert("IndividualID",SqlField (SQLFIELD_LINK,true,"Individual"));
    m_fieldTypeList.insert("MaterialTypeID",SqlField (SQLFIELD_LINK,true,"MaterialType",true));
    m_fieldTypeList.insert("InventoryNumber",SqlField (SQLFIELD_TEXT,false));
    m_fieldTypeList.insert("Parity",SqlField (SQLFIELD_SPECIAL,true,"Parity"));
    m_fieldTypeList.insert("Completeness",SqlField (SQLFIELD_SPECIAL,true,"Completeness"));
    m_fieldTypeList.insert("Comments",SqlField (SQLFIELD_TEXT,false));


}

void MaterialSqlTable::constructModels()
{
    m_tableModel = new MaterialTableModel(&m_data);
    m_listModel = new MaterialListModel(&m_data);
}


