#ifndef MATERIALLISTMODEL_H
#define MATERIALLISTMODEL_H

#include "ListModel/abstractsqllistmodel.h"

class MaterialListModel : public AbstractSqlListModel
{
public:
    MaterialListModel(QList<SqlDatum> *data = nullptr);

    QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const;
};

#endif // MATERIALLISTMODEL_H
