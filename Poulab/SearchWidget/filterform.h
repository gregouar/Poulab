/** This not very well designed class represent a row in the form of all filters for the SearchWidget.
 * A filter is a basic WHERE sql query part that is automatically constructed from inputs chosed by the user.
**/

#ifndef FILTERFORM_H
#define FILTERFORM_H

#include <QObject>

#include <QComboBox>
#include <QHBoxLayout>
#include "CustomWidgets/partiallyeditabletextbox.h"
#include "SqlTable/abstractsqltable.h"

class FilterForm : public QObject
{
    Q_OBJECT

public:
    FilterForm(QComboBox *tableCBox,QHBoxLayout *inputLayout,
               const NonEditablePart *fieldNonEditablePart,
                const NonEditablePart* opNonEditablePart,
                const DbManager* db);
    ~FilterForm();

    void setEnableOperatorCBox(bool = true);
    QString getTableName();

    void updateTableBox(const QList<QString> &list);
    int lookForField(const QString &fieldName);
    void setField(const QString &fieldname);

public slots:
    void changeTable(int);
    void changeField(int);
    void changeOperator();
    void setInputValue(QVariant);
    void inputValueChanged();

    void modelReset();

signals:
    void askToChangeNonEditablePart(const NonEditablePart*,QString);
    void askToDeleteNonEditablePart(const NonEditablePart*);

protected:
    void generateFieldList();
    void generateInputField();
    QVariant readInputValue();

private:
    QHBoxLayout* m_layout;

    QComboBox *m_tableCBox;
    QHBoxLayout *m_fieldCBoxLayout;
    QComboBox *m_fieldCBox;
    const NonEditablePart *m_fieldNonEditablePart;

    QHBoxLayout *m_opCBoxLayout;
    QComboBox *m_opCBox;
    const NonEditablePart *m_opNonEditablePart;

    QHBoxLayout* m_inputLayout;
    QWidget* m_input;

    const AbstractSqlTable* m_curSqlTable;
    const SqlField *m_sqlField;
    const DbManager *m_db;

    int m_lastTableIndex;
    int m_lastFieldIndex;
    QVariant m_oldValue;
};

#endif // FILTERFORM_H
