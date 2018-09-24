#ifndef MUSEUMLISTMODEL_H
#define MUSEUMLISTMODEL_H

#include "ListModel/abstractsqllistmodel.h"

class MuseumListModel : public AbstractSqlListModel
{
public:
    MuseumListModel(QList<SqlDatum> *data = nullptr);

    QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const;
};

#endif // MUSEUMLISTMODEL_H

