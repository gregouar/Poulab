#ifndef ADDMATERIALWIDGET_H
#define ADDMATERIALWIDGET_H

#include "AddItemWidget/abstractadditemwidget.h"

namespace Ui {
class AddMaterialWidget;
}

class AddMaterialWidget : public AbstractAddItemWidget
{
public:
    explicit AddMaterialWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    ~AddMaterialWidget();

private:
    Ui::AddMaterialWidget *ui;
};

#endif // ADDMATERIALWIDGET_H
