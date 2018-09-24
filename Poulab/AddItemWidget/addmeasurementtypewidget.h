#ifndef ADDMEASUREMENTTYPEWIDGET_H
#define ADDMEASUREMENTTYPEWIDGET_H

#include "AddItemWidget/abstractadditemwidget.h"


namespace Ui {
class AddMeasurementTypeWidget;
}


class AddMeasurementTypeWidget : public AbstractAddItemWidget
{
    Q_OBJECT

public:
    explicit AddMeasurementTypeWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    ~AddMeasurementTypeWidget();

protected slots:
    void updatePicture(int v = -1);
    void browsePicture();

protected:
    QPixmap m_img;

private:
    Ui::AddMeasurementTypeWidget *ui;

};

#endif // ADDMEASUREMENTTYPEWIDGET_H
