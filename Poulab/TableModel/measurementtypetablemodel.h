/** This one allows to reorder elements using drag and drops. **/

#ifndef MEASUREMENTTYPETABLEMODEL_H
#define MEASUREMENTTYPETABLEMODEL_H

#include "TableModel/abstractsqltablemodel.h"

class MeasurementTypeTableModel : public AbstractSqlTableModel
{
public:
    MeasurementTypeTableModel(QList<SqlDatum> *data = nullptr);

    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    Qt::DropActions supportedDropActions() const;

    QStringList mimeTypes() const;
    QMimeData * mimeData(const QModelIndexList & indexes) const;
    bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent);

protected:
    virtual QVariant generateStoredValue(const SqlDatum*, int column) const;
};

#endif // MEASUREMENTTYPETABLEMODEL_H
