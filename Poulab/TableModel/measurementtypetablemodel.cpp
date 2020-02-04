#include "measurementtypetablemodel.h"

#include "dbmanager.h"

#include <QDebug>
#include <QMimeData>
#include <QDataStream>

MeasurementTypeTableModel::MeasurementTypeTableModel(QList<SqlDatum> *data)
    : AbstractSqlTableModel(data)
{

}

int MeasurementTypeTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant MeasurementTypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                    return .2;
            break;

            case 2:
                if (role == Qt::DisplayRole)
                   return tr("Comments");
                else if(role == Qt::SizeHintRole)
                    return .5;
            break;

            case 3:
                if (role == Qt::DisplayRole)
                    return tr("Material type");
            break;


            default:
                return QVariant();
        }
    }
    return QVariant();
}



QVariant MeasurementTypeTableModel::generateStoredValue(const SqlDatum *datum, int column) const
{
    if(datum == nullptr || !datum->isValid())
        return QVariant();

    DbManager *parentDb = datum->getParentTable()->getParentDb();

    switch(column)
    {
        case 1:
            return datum->getFieldValue("Name");
        break;

        case 2:
            return datum->getFieldValue("Comments");
        break;

        case 3:
            return parentDb->getItemListName("MaterialType",datum->getFieldValue("MaterialTypeID").toInt());
        break;

        default:
            return QVariant();
    }
}

Qt::ItemFlags MeasurementTypeTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

Qt::DropActions MeasurementTypeTableModel::supportedDropActions() const
{
    return Qt::MoveAction /*| Qt::CopyAction*/;
}

QStringList MeasurementTypeTableModel::mimeTypes() const
{
    QStringList types;
    types << "list.int";
    return types;
}

QMimeData *MeasurementTypeTableModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid() && index.column() == 0) {
            stream << index.row();
        }
    }

    mimeData->setData("list.int", encodedData);
    return mimeData;
}

bool MeasurementTypeTableModel::dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & index)
{
    if (action == Qt::IgnoreAction)
           return true;

   if (!data->hasFormat("list.int"))
       return false;

   if (column > 0)
       return false;


   int beginRow = row;

   if(index.isValid())
       beginRow = index.row();
   else
       beginRow = this->rowCount(QModelIndex());

   QByteArray encodedData = data->data("list.int");
   QDataStream stream(&encodedData, QIODevice::ReadOnly);

   const AbstractSqlTable *table = m_data->first().getParentTable();
   QString sorterField = table->retrieveSorterField();

   QList<int> movedRows;
   while (!stream.atEnd()) {
       int r;
       stream >> r;
       movedRows.push_back(r);
   }

   if(movedRows.size() == m_data->size())
       return true;

   std::sort(movedRows.begin(), movedRows.end());

   int movedRowsStartIndex = movedRows.first();
   bool movingUpward = movedRowsStartIndex > beginRow;

   int curWeight = 0;

   if(beginRow < m_data->size())
   {
       SqlDatum & datum = (*m_data)[beginRow];
       curWeight = datum.getFieldValue(sorterField).toInt() + !movingUpward;
   } else
       curWeight = m_data->last().getFieldValue(sorterField).toInt()+1;

   for(int i = beginRow + !movingUpward ; i < this->rowCount() ; ++i)
   {
        SqlDatum & datum = (*m_data)[i];
       int weight = datum.getFieldValue(sorterField).toInt();
       weight += movedRows.size();
       datum.setFieldValue(sorterField,weight);
       datum.addToTable();
   }
   for(int i = 0 ; i < movedRows.size() ; ++i)
   {
        SqlDatum & datum = (*m_data)[movedRows[i]];
       datum.setFieldValue(sorterField,curWeight++);
       datum.addToTable();
   }


   QList<SqlDatum> tempDataList;
   while(!movedRows.empty())
       tempDataList.push_front(m_data->takeAt(movedRows.takeLast()));
   while(!tempDataList.isEmpty())
     m_data->insert(beginRow,tempDataList.takeLast());


   this->reset();

   return true;
}


