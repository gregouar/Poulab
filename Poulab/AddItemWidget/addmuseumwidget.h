#ifndef ADDMUSEUMWIDGET_H
#define ADDMUSEUMWIDGET_H

#include <QWidget>
#include "AddItemWidget/abstractadditemwidget.h"

namespace Ui {
class AddMuseumWidget;
}

class AddMuseumWidget : public AbstractAddItemWidget
{
    Q_OBJECT
public:
    explicit AddMuseumWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    ~AddMuseumWidget();

private:
    Ui::AddMuseumWidget *ui;
};

#endif // ADDMUSEUMWIDGET_H


