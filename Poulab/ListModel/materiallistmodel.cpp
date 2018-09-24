#include "materiallistmodel.h"
#include "dbmanager.h"


MaterialListModel::MaterialListModel(QList<SqlDatum> *data) :
    AbstractSqlListModel(data)
{
}

QVariant MaterialListModel::getDataFromSqlDatum(const SqlDatum *datum, int role) const
{
    DbManager *parentDb = datum->getParentTable()->getParentDb();
    if (role == Qt::DisplayRole)
        return datum->getFieldValue("InventoryNumber").toString()
                +" ("+parentDb->getItemListName("MaterialType",datum->getFieldValue("MaterialTypeID").toInt())+")";
    else if (role == Qt::UserRole)
        return datum->getID();
    return QVariant();
}
