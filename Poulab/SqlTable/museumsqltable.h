#ifndef MUSEUMSQLTABLE_H
#define MUSEUMSQLTABLE_H

#include "SqlTable/abstractsqltable.h"

class MuseumSqlTable : public AbstractSqlTable
{
public:
    MuseumSqlTable(DbManager* parentDb);

    virtual void createNewTable();

    virtual void constructModels();

protected:
};

#endif // MUSEUMSQLTABLE_H
