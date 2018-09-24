#ifndef ADDMATERIALTYPEWIDGET_H
#define ADDMATERIALTYPEWIDGET_H

#include <QWidget>
#include "AddItemWidget/abstractadditemwidget.h"

namespace Ui {
class AddMaterialTypeWidget;
}

class AddMaterialTypeWidget : public AbstractAddItemWidget
{
    Q_OBJECT

public:
    explicit AddMaterialTypeWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    ~AddMaterialTypeWidget();

private:
    Ui::AddMaterialTypeWidget *ui;

};

#endif // ADDMATERIALTYPEWIDGET_H
