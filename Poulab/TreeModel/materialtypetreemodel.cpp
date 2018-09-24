#include "materialtypetreemodel.h"

#include <QDebug>

MaterialTypeTreeModel::MaterialTypeTreeModel(QList<SqlDatum> *data, AbstractSqlTable *parentTable) :
    AbstractSqlTreeModel(data,parentTable)
{
    m_parentingField = "ParentMaterialTypeID";
    initializeData();
}


QVariant MaterialTypeTreeModel::getDataFromSqlDatum(const SqlDatum *datum, int role) const
{
    if(datum == nullptr)
        return QVariant();

    if (role == Qt::DisplayRole)
        return datum->getFieldValue("Name").toString();
    else if (role == Qt::UserRole)
        return datum->getID();

    return QVariant();
}
