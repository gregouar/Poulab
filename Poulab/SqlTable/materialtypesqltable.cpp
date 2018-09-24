#include "materialtypesqltable.h"
#include "TableModel/materialtypetablemodel.h"
#include "ListModel/materialtypelistmodel.h"
#include "TreeModel/materialtypetreemodel.h"

MaterialTypeSqlTable::MaterialTypeSqlTable(DbManager* parentDb) :
    AbstractSqlTable(parentDb)
{
    m_tableName = "MaterialType";
    m_mainChild = "MeasurementType";

    m_fieldTypeList.insert("Name",SqlField (SQLFIELD_TEXT,true));
    m_fieldTypeList.insert("ParentMaterialTypeID",SqlField (SQLFIELD_LINK,false,"MaterialType",true));

}

void MaterialTypeSqlTable::constructModels()
{
    m_tableModel = new MaterialTypeTableModel(&m_data);
    m_listModel = new MaterialTypeListModel(&m_data);
    m_treeModel = new MaterialTypeTreeModel(&m_data, this);
}



