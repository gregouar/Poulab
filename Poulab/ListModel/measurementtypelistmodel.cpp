#include "measurementtypelistmodel.h"


MeasurementTypeListModel::MeasurementTypeListModel(QList<SqlDatum> *data) :
    AbstractSqlListModel(data)
{
}

QVariant MeasurementTypeListModel::getDataFromSqlDatum(const SqlDatum *datum, int role) const
{
    if (role == Qt::DisplayRole)
        return datum->getFieldValue("Name").toString();
    else if (role == Qt::UserRole)
        return datum->getID();
    else if (role == Qt::ToolTipRole)
        return datum->getFieldValue("Comments").toString();
    return QVariant();
}
