#ifndef MEASUREMENTTYPELISTMODEL_H
#define MEASUREMENTTYPELISTMODEL_H

#include "ListModel/abstractsqllistmodel.h"

class MeasurementTypeListModel : public AbstractSqlListModel
{
public:
    MeasurementTypeListModel(QList<SqlDatum> *data = nullptr);

    QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const;
};

#endif // MEASUREMENTTYPELISTMODEL_H
