#ifndef MATERIALSQLTABLE_H
#define MATERIALSQLTABLE_H

#include "SqlTable/abstractsqltable.h"

class MaterialSqlTable : public AbstractSqlTable
{
public:
    MaterialSqlTable(DbManager* parentDb);

    virtual void constructModels();
};

#endif // MATERIALSQLTABLE_H


