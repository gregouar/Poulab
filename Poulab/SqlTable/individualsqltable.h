#ifndef INDIVIDUALSQLTABLE_H
#define INDIVIDUALSQLTABLE_H

#include "SqlTable/abstractsqltable.h"

class IndividualSqlTable : public AbstractSqlTable
{
public:
    IndividualSqlTable(DbManager* parentDb);

    virtual void constructModels();

};

#endif // INDIVIDUALSQLTABLE_H

