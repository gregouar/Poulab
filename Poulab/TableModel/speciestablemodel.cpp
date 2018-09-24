#include "speciestablemodel.h"

SpeciesTableModel::SpeciesTableModel(QList<SqlDatum> *data)
    : AbstractSqlTableModel(data)
{

}

int SpeciesTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

QVariant SpeciesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                   return tr("Genus");
                else if(role == Qt::SizeHintRole)
                    return .2;
            break;

            case 2:
                if (role == Qt::DisplayRole)
                   return tr("Name");
                else if(role == Qt::SizeHintRole)
                    return .15;
            break;

            case 3:
                if (role == Qt::DisplayRole)
                   return tr("Subfamily");
                else if(role == Qt::SizeHintRole)
                    return .15;
            break;

            case 4:
                if (role == Qt::DisplayRole)
                   return tr("Family");
                else if(role == Qt::SizeHintRole)
                    return .15;
            break;

            case 5:
                if (role == Qt::DisplayRole)
                    return tr("Clade");
            break;

            default:
                return QVariant();
        }
    }
    return QVariant();
}



QVariant SpeciesTableModel::generateStoredValue(const SqlDatum *datum, int column) const
{
    if(datum == nullptr || !datum->isValid())
        return QVariant();

    switch(column)
    {
        case 1:
            return datum->getFieldValue("Genus");
        break;

        case 2:
            return datum->getFieldValue("Name");
        break;

        case 3:
            return datum->getFieldValue("Subfamily");
        break;

        case 4:
            return datum->getFieldValue("Family");
        break;

        case 5:
            return datum->getFieldValue("Clade");
        break;

        default:
            return QVariant();
    }
}


