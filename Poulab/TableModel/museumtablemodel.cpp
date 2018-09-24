#include "museumtablemodel.h"



MuseumTableModel::MuseumTableModel(QList<SqlDatum> *data)
    : AbstractSqlTableModel(data)
{

}

int MuseumTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant MuseumTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                   return tr("Name");
                else if(role == Qt::SizeHintRole)
                    return .45;
            break;

            case 2:
                if (role == Qt::DisplayRole)
                   return tr("Country");
            break;

            default:
                return QVariant();
        }
    }
    return QVariant();
}


QVariant MuseumTableModel::generateStoredValue(const SqlDatum *datum, int column) const
{
    if(datum == nullptr || !datum->isValid())
        return QVariant();

    switch(column)
    {
        case 1:
            return datum->getFieldValue("Name");
        break;

        case 2:
            return datum->getFieldValue("Country");
        break;

        default:
            return QVariant();
    }
}


