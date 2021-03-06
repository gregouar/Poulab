#include "individualsqltable.h"

#include "TableModel/individualtablemodel.h"
#include "ListModel/individuallistmodel.h"

IndividualSqlTable::IndividualSqlTable(DbManager* parentDb) :
    AbstractSqlTable(parentDb)
{
    m_tableName = "Individual";
    m_mainChild = "Material";

    m_fieldTypeList.insert("SpeciesID",SqlField (SQLFIELD_LINK,true,"Species"));
    m_fieldTypeList.insert("MuseumID",SqlField (SQLFIELD_LINK,true,"Museum"));
    m_fieldTypeList.insert("Hypodigme",SqlField (SQLFIELD_SPECIAL,true,"Hypodigme"));
    m_fieldTypeList.insert("InventoryNumber",SqlField (SQLFIELD_TEXT,false));
    m_fieldTypeList.insert("Maturity",SqlField (SQLFIELD_SPECIAL,true,"Maturity"));
    m_fieldTypeList.insert("Thanatocoenosis",SqlField (SQLFIELD_SPECIAL,true,"Thanatocoenosis"));
}

void IndividualSqlTable::constructModels()
{
    m_tableModel = new IndividualTableModel(&m_data);
    m_listModel = new IndividualListModel(&m_data);
}




