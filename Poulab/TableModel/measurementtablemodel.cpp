#include "measurementtablemodel.h"

#include "dbmanager.h"


MeasurementTableModel::MeasurementTableModel(QList<SqlDatum> *data)
    : AbstractSqlTableModel(data)
{

}

int MeasurementTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant MeasurementTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                     return tr("Measurement type");
                else if(role == Qt::SizeHintRole)
                    return .25;
            break;

            case 2:
                if (role == Qt::DisplayRole)
                    return tr("Value");
                else if(role == Qt::SizeHintRole)
                    return .25;
            break;

            case 3:
                if (role == Qt::DisplayRole)
                    return tr("Description");
            break;



            default:
                return QVariant();
        }
    }
    return QVariant();
}



QVariant MeasurementTableModel::generateStoredValue(const SqlDatum *datum, int column) const
{
    if(datum == nullptr || !datum->isValid())
        return QVariant();

    DbManager *parentDb = datum->getParentTable()->getParentDb();

    switch(column)
    {
        case 1:
            return parentDb->getItemListName("MeasurementType",datum->getFieldValue("MeasurementTypeID").toInt());
        break;

        case 2:
            return datum->getFieldValue("Value");
        break;

        case 3:
        {
            SqlDatum mD = parentDb->getDatumFromId("MeasurementType",datum->getFieldValue("MeasurementTypeID").toInt());
            return mD.getFieldValue("Comments");
        }
        break;

        default:
            return QVariant();
    }
}
