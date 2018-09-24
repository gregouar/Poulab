#include "measurementlistmodel.h"
#include "dbmanager.h"


MeasurementListModel::MeasurementListModel(QList<SqlDatum> *data) :
    AbstractSqlListModel(data)
{
}

QVariant MeasurementListModel::getDataFromSqlDatum(const SqlDatum *datum, int role) const
{
    DbManager *parentDb = datum->getParentTable()->getParentDb();
    if (role == Qt::DisplayRole)
        return parentDb->getItemListName("MeasurementType",datum->getFieldValue("MeasurementTypeID").toInt())
                +" ("+datum->getFieldValue("Value").toString()+")";
    else if (role == Qt::UserRole)
        return datum->getID();
    return QVariant();
}
