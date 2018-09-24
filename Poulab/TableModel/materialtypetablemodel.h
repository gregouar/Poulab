#ifndef MATERIALTYPETABLEMODEL_H
#define MATERIALTYPETABLEMODEL_H

#include "TableModel/abstractsqltablemodel.h"

class MaterialTypeTableModel : public AbstractSqlTableModel
{
public:
    MaterialTypeTableModel(QList<SqlDatum> *data = nullptr);

    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    virtual QVariant generateStoredValue(const SqlDatum*, int column) const;
};

#endif // MATERIALTYPETABLEMODEL_H
