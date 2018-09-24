#ifndef MATERIALTYPETREEMODEL_H
#define MATERIALTYPETREEMODEL_H

#include "TreeModel/abstractsqltreemodel.h"

class MaterialTypeTreeModel : public AbstractSqlTreeModel
{
public:
    MaterialTypeTreeModel(QList<SqlDatum> *data = nullptr, AbstractSqlTable *parentTable = nullptr);

    virtual QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const;
};




#endif // MATERIALTYPETREEMODEL_H
