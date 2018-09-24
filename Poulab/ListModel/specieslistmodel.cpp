#include "specieslistmodel.h"


SpeciesListModel::SpeciesListModel(QList<SqlDatum> *data) :
    AbstractSqlListModel(data)
{
}

QVariant SpeciesListModel::getDataFromSqlDatum(const SqlDatum *datum, int role) const
{
    if (role == Qt::DisplayRole)
        return datum->getFieldValue("Genus").toString()+" "+datum->getFieldValue("Name").toString();
    else if (role == Qt::UserRole)
        return datum->getID();
    return QVariant();
}

