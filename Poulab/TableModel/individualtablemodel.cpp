#include "individualtablemodel.h"

#include "dbmanager.h"


IndividualTableModel::IndividualTableModel(QList<SqlDatum> *data)
    : AbstractSqlTableModel(data)
{

}

int IndividualTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant IndividualTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                   return tr("Species");
                else if(role == Qt::SizeHintRole)
                    return .15;
            break;

            case 2:
                if (role == Qt::DisplayRole)
                   return tr("Museum");
                else if(role == Qt::SizeHintRole)
                    return .1;
            break;

            case 3:
                if (role == Qt::DisplayRole)
                   return tr("Hypodigme");
                else if(role == Qt::SizeHintRole)
                    return .1;
            break;

            case 4:
                if (role == Qt::DisplayRole)
                   return tr("Inventory number");
            break;

            default:
                return QVariant();
        }
    }
    return QVariant();
}

QVariant IndividualTableModel::generateStoredValue(const SqlDatum *datum, int column) const
{
    if(datum == nullptr || !datum->isValid())
        return QVariant();

    DbManager *parentDb = datum->getParentTable()->getParentDb();

    switch(column)
    {
        case 1:
            return parentDb->getItemListName("Species", datum->getFieldValue("SpeciesID").toInt());
        break;

        case 2:
            return parentDb->getItemListName("Museum",datum->getFieldValue("MuseumID").toInt());
        break;

        case 3:
            return SqlField::getSpecialType("Hypodigme",datum->getFieldValue("Hypodigme").toInt());
        break;

        case 4:
        {
            auto invNbr = datum->getFieldValue("InventoryNumber");
            if(!invNbr.isNull() && !invNbr.toString().isEmpty())
                return invNbr;

            QSqlQuery query;
            query.exec("SELECT InventoryNumber FROM Material WHERE IndividualID = "+QVariant(datum->getID()).toString()+";");
            QString s;
            bool first = true;
            while(query.next())
            {
                if(!first) s+= +", ";
                s += query.value(0).toString();
                first = false;
            }
            return "Materials: "+s;
        }
        break;

        default:
            return QVariant();
    }
}
