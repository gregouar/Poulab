#ifndef MATERIALTYPESQLTABLE_H
#define MATERIALTYPESQLTABLE_H

#include "SqlTable/abstractsqltable.h"

class MaterialTypeSqlTable : public AbstractSqlTable
{
public:
    MaterialTypeSqlTable(DbManager* parentDb);

    virtual void constructModels();
};

#endif // MATERIALTYPESQLTABLE_H

