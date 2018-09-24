#ifndef SPECIESSQLTABLE_H
#define SPECIESSQLTABLE_H

#include "SqlTable/abstractsqltable.h"

class SpeciesSqlTable : public AbstractSqlTable
{
public:
    SpeciesSqlTable(DbManager* parentDb);

    virtual void constructModels();
};

#endif // SPECIESSQLTABLE_H


