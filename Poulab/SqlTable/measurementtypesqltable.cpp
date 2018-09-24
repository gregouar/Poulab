#include "measurementtypesqltable.h"
#include "TableModel/measurementtypetablemodel.h"
#include "ListModel/measurementtypelistmodel.h"

MeasurementTypeSqlTable::MeasurementTypeSqlTable(DbManager* parentDb) :
    AbstractSqlTable(parentDb)
{
    m_tableName = "MeasurementType";

    m_fieldTypeList.insert("Name",SqlField (SQLFIELD_TEXT,true));
    m_fieldTypeList.insert("MaterialTypeID",SqlField (SQLFIELD_LINK,true,"MaterialType",true));
    m_fieldTypeList.insert("Comments",SqlField (SQLFIELD_TEXT,false));
    m_fieldTypeList.insert("Picture",SqlField (SQLFIELD_TEXT,false));
    m_fieldTypeList.insert("SortingWeight",SqlField (SQLFIELD_SORTER,false));
}


void MeasurementTypeSqlTable::constructModels()
{
    m_tableModel = new MeasurementTypeTableModel(&m_data);
    m_listModel = new MeasurementTypeListModel(&m_data);
}
