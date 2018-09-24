#include "individuallistmodel.h"
#include "dbmanager.h"

IndividualListModel::IndividualListModel(QList<SqlDatum> *data) :
    AbstractSqlListModel(data)
{
}

QVariant IndividualListModel::getDataFromSqlDatum(const SqlDatum *datum, int role) const
{
    DbManager *parentDb = datum->getParentTable()->getParentDb();
    if (role == Qt::DisplayRole)
        return parentDb->getItemListName("Species",datum->getFieldValue("SpeciesID").toInt()) + " in " +
                parentDb->getItemListName("Museum",datum->getFieldValue("MuseumID").toInt());
    else if (role == Qt::UserRole)
        return datum->getID();
    return QVariant();
}
