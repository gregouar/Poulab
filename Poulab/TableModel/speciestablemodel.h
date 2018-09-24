#ifndef SPECIESTABLEMODEL_H
#define SPECIESTABLEMODEL_H

#include "TableModel/abstractsqltablemodel.h"

class SpeciesTableModel : public AbstractSqlTableModel
{
public:
    SpeciesTableModel(QList<SqlDatum> *data = nullptr);

    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    virtual QVariant generateStoredValue(const SqlDatum*, int column) const;
};

#endif // SPECIESTABLEMODEL_H


