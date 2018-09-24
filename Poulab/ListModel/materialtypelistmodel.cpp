#include "materialtypelistmodel.h"



MaterialTypeListModel::MaterialTypeListModel(QList<SqlDatum> *data) :
    AbstractSqlListModel(data)
{
}

QVariant MaterialTypeListModel::getDataFromSqlDatum(const SqlDatum *datum, int role) const
{
    if (role == Qt::DisplayRole)
        return datum->getFieldValue("Name").toString();
    else if (role == Qt::UserRole)
        return datum->getID();
    return QVariant();
}

