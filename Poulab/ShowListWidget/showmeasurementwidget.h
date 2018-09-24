/** We change the classical Open button of ShowList widget to an Edit one. **/

#ifndef SHOWMEASUREMENTWIDGET_H
#define SHOWMEASUREMENTWIDGET_H

#include "showlistwidget.h"

class ShowMeasurementWidget : public ShowListWidget
{
    Q_OBJECT
public:
    ShowMeasurementWidget(QWidget *parent = nullptr);
    virtual ~ShowMeasurementWidget();

    virtual void setTableModel(QAbstractItemModel *model, bool explorable = false);

public slots:
   virtual void openButtonClicked();

signals:
    void askToAddAllMeasurements();
};

#endif // SHOWMEASUREMENTWIDGET_H
