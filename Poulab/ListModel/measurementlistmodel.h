#ifndef MEASUREMENTLISTMODEL_H
#define MEASUREMENTLISTMODEL_H

#include "ListModel/abstractsqllistmodel.h"

class MeasurementListModel : public AbstractSqlListModel
{
public:
    MeasurementListModel(QList<SqlDatum> *data = nullptr);

    QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const;
};

#endif // MEASUREMENTLISTMODEL_H
