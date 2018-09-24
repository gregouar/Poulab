#ifndef MATERIALTABLEMODEL_H
#define MATERIALTABLEMODEL_H

#include "TableModel/abstractsqltablemodel.h"

class MaterialTableModel : public AbstractSqlTableModel
{
public:
    MaterialTableModel(QList<SqlDatum> *data = nullptr);

    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    virtual QVariant generateStoredValue(const SqlDatum*, int column) const;
};

#endif // MATERIALTABLEMODEL_H
