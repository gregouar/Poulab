#include "materialtablemodel.h"

#include "dbmanager.h"

MaterialTableModel::MaterialTableModel(QList<SqlDatum> *data)
    : AbstractSqlTableModel(data)
{

}

int MaterialTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant MaterialTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        switch (section) {

            case 0:
              if (role == Qt::DisplayRole)
                 return tr("ID");
              else if(role == Qt::SizeHintRole)
                  return .05;
            break;


            case 1:
                if (role == Qt::DisplayRole)
                   return tr("Material type");
                else if(role == Qt::SizeHintRole)
                    return .3;
            break;

            case 2:
                if (role == Qt::DisplayRole)
                   return tr("Inventory nbr");
                else if(role == Qt::SizeHintRole)
                    return .3;
            break;

            case 3:
                if (role == Qt::DisplayRole)
                   return tr("Parity");
                else if(role == Qt::SizeHintRole)
                    return .175;
            break;

            case 4:
                if (role == Qt::DisplayRole)
                    return tr("Completeness");
            break;

            default:
                return QVariant();
        }
    }
    return QVariant();
}



QVariant MaterialTableModel::generateStoredValue(const SqlDatum *datum, int column) const
{
    if(datum == nullptr || !datum->isValid())
        return QVariant();

    DbManager *parentDb = datum->getParentTable()->getParentDb();

    switch(column)
    {
        case 1:
            return parentDb->getItemListName("MaterialType",datum->getFieldValue("MaterialTypeID").toInt());
        break;

        case 2:
            return datum->getFieldValue("InventoryNumber");
        break;

        case 3:
            return SqlField::getSpecialType("Parity",datum->getFieldValue("Parity").toInt());
        break;

        case 4:
            return SqlField::getSpecialType("Completeness",datum->getFieldValue("Completeness").toInt());
        break;

        default:
            return QVariant();
    }
}



