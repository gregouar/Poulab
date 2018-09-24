#ifndef MATERIALTYPELISTMODEL_H
#define MATERIALTYPELISTMODEL_H

#include "ListModel/abstractsqllistmodel.h"

class MaterialTypeListModel : public AbstractSqlListModel
{
public:
    MaterialTypeListModel(QList<SqlDatum> *data = nullptr);

    QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const;
};

#endif // MATERIALTYPELISTMODEL_H
