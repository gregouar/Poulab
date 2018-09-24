#ifndef MEASUREMENTSQLTABLE_H
#define MEASUREMENTSQLTABLE_H

#include "SqlTable/abstractsqltable.h"

class MeasurementSqlTable : public AbstractSqlTable
{
public:
    MeasurementSqlTable(DbManager* parentDb);

    virtual void constructModels();
};

#endif // MEASUREMENTSQLTABLE_H


