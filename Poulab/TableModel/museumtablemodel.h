#ifndef MUSEUMTABLEMODEL_H
#define MUSEUMTABLEMODEL_H

#include "TableModel/abstractsqltablemodel.h"

class MuseumTableModel : public AbstractSqlTableModel
{
public:
    MuseumTableModel(QList<SqlDatum> *data = nullptr);

    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    QVariant generateStoredValue(const SqlDatum*, int column) const;
};

#endif // MUSEUMTABLEMODEL_H
