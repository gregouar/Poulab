#include "measurementsqltable.h"
#include "TableModel/measurementtablemodel.h"
#include "ListModel/measurementlistmodel.h"

MeasurementSqlTable::MeasurementSqlTable(DbManager* parentDb) :
    AbstractSqlTable(parentDb)
{
    m_tableName = "Measurement";

    m_fieldTypeList.insert("Value",SqlField (SQLFIELD_REAL,true));
    m_fieldTypeList.insert("MaterialID",SqlField (SQLFIELD_LINK,true,"Material"));
    m_fieldTypeList.insert("MeasurementTypeID",SqlField (SQLFIELD_LINK,true,"MeasurementType"));

}

void MeasurementSqlTable::constructModels()
{
    m_tableModel = new MeasurementTableModel(&m_data);
    m_listModel = new MeasurementListModel(&m_data);
}






