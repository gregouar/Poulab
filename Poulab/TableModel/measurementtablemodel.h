#ifndef MEASUREMENTTABLEMODEL_H
#define MEASUREMENTTABLEMODEL_H

#include "TableModel/abstractsqltablemodel.h"

class MeasurementTableModel : public AbstractSqlTableModel
{
public:
    MeasurementTableModel(QList<SqlDatum> *data = nullptr);

    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    virtual QVariant generateStoredValue(const SqlDatum*, int column) const;
};

#endif // MEASUREMENTTABLEMODEL_H
