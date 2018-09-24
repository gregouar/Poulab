#ifndef ADDSPECIESWIDGET_H
#define ADDSPECIESWIDGET_H

#include "AddItemWidget/abstractadditemwidget.h"

namespace Ui {
class AddSpeciesWidget;
}

class AddSpeciesWidget : public AbstractAddItemWidget
{
    Q_OBJECT
public:
    explicit AddSpeciesWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    ~AddSpeciesWidget();

private:
    Ui::AddSpeciesWidget *ui;
};

#endif // ADDSPECIESWIDGET_H

