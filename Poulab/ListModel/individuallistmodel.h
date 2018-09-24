#ifndef INDIVIDUALLISTMODEL_H
#define INDIVIDUALLISTMODEL_H

#include "ListModel/abstractsqllistmodel.h"

class IndividualListModel : public AbstractSqlListModel
{
public:
    IndividualListModel(QList<SqlDatum> *data = nullptr);

    QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const;
};

#endif // INDIVIDUALLISTMODEL_H
