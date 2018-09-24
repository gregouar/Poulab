#ifndef MEASUREMENTTYPESQLTABLE_H
#define MEASUREMENTTYPESQLTABLE_H

#include "SqlTable/abstractsqltable.h"

class MeasurementTypeSqlTable : public AbstractSqlTable
{
public:
    MeasurementTypeSqlTable(DbManager* parentDb);

    virtual void constructModels();
};


#endif // MEASUREMENTTYPESQLTABLE_H
