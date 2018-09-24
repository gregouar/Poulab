#ifndef INDIVIDUALTABLEMODEL_H
#define INDIVIDUALTABLEMODEL_H

#include "TableModel/abstractsqltablemodel.h"

class IndividualTableModel : public AbstractSqlTableModel
{
public:
    IndividualTableModel(QList<SqlDatum> *data = nullptr);

    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    QVariant generateStoredValue(const SqlDatum*, int column) const;

};

#endif // INDIVIDUALTABLEMODEL_H



