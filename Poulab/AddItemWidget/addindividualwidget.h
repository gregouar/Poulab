#ifndef ADDINDIVIDUALWIDGET_H
#define ADDINDIVIDUALWIDGET_H

#include <QWidget>
#include "AddItemWidget/abstractadditemwidget.h"


namespace Ui {
class AddIndividualWidget;
}


class AddIndividualWidget : public AbstractAddItemWidget
{
    Q_OBJECT

public:
    explicit AddIndividualWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    ~AddIndividualWidget();

private:
    Ui::AddIndividualWidget *ui;

};

#endif // ADDINDIVIDUALWIDGET_H



