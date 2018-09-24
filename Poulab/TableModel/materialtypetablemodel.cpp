#include "materialtypetablemodel.h"

#include "dbmanager.h"


MaterialTypeTableModel::MaterialTypeTableModel(QList<SqlDatum> *data)
    : AbstractSqlTableModel(data)
{

}

int MaterialTypeTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant MaterialTypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            break;

            default:
                return QVariant();
        }
    }
    return QVariant();
}

QVariant MaterialTypeTableModel::generateStoredValue(const SqlDatum *datum, int column) const
{
    if(datum == nullptr || !datum->isValid())
        return QVariant();

    switch(column)
    {
        case 1:
            return datum->getFieldValue("Name");
        break;

        default:
            return QVariant();
    }
}
