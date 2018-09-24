#ifndef ADDMEASUREMENTWIDGET_H
#define ADDMEASUREMENTWIDGET_H

#include "AddItemWidget/abstractadditemwidget.h"

namespace Ui {
class AddMeasurementWidget;
}

class AddMeasurementWidget : public AbstractAddItemWidget
{
    Q_OBJECT
public:
    explicit AddMeasurementWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    virtual ~AddMeasurementWidget();

    virtual void setDatum(const SqlDatum &datum);

private slots:
    void materialChanged(int);
    void measurementTypeChanged(int);

private:
    Ui::AddMeasurementWidget *ui;
    bool m_disableMeasurementTypeChange;

    QPixmap m_img;
};

#endif // ADDMEASUREMENTWIDGET_H
