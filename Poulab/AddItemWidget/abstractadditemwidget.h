/** This widget that should be inherited will take care to automatically add/edit
 * records in the given table. You need to construct the layout by hand and connect
 * inputs to their corresponding field on the table by adding them in the m_inputsList
 * as <FieldName, InputWidget>
 * Then inputs are then automatically filled in function of the database.
 **/

#ifndef ABSTRACTADDITEMWIDGET_H
#define ABSTRACTADDITEMWIDGET_H

#include <QWidget>

#include "SqlDatum/sqldatum.h"

namespace Ui {
class AddItemWidget;
}

class AbstractAddItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractAddItemWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    virtual ~AbstractAddItemWidget();

    virtual void setDatum(const SqlDatum &datum);

    void setParentDefaultChoice(const QString &parentField, int ID);


signals:
    void itemAdded();
    void itemDeleted();
    void cancel();

    void datumSet(int);

public slots:
    virtual void addItem(const SqlDatum* datum = nullptr);
    void deleteItem();

protected:
    int getCurDatumID();
    void generateInputFields();

    SqlDatum m_curDatum;
    const AbstractSqlTable *m_sqlTable;

    QMap<QString, QObject*> m_inputsList;

    Ui::AddItemWidget *mainui;
};

#endif // ABSTRACTADDITEMWIDGET_H
