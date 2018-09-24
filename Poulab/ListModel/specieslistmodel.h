#ifndef SPECIESLISTMODEL_H
#define SPECIESLISTMODEL_H

#include "ListModel/abstractsqllistmodel.h"

class SpeciesListModel : public AbstractSqlListModel
{
public:
    SpeciesListModel(QList<SqlDatum> *data = nullptr);

    QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const;
};

#endif // SPECIESLISTMODEL_H

