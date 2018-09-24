/** This version of ShowListWidget allow to copy MeasurementType from on MaterialType to another.
 * In addition, it allows to choose a sorting order for MeasurementType using drag and drop.
 * Because of that, any sort of other resorting is disabled.
**/

#ifndef SHOWMEASUREMENTTYPEWIDGET_H
#define SHOWMEASUREMENTTYPEWIDGET_H


#include "showlistwidget.h"

#include "dbmanager.h"

class ShowMeasurementTypeWidget : public ShowListWidget
{
    Q_OBJECT
public:
    ShowMeasurementTypeWidget(DbManager *db, QWidget *parent = nullptr);
    virtual ~ShowMeasurementTypeWidget();

public slots:
   virtual void openButtonClicked();

protected slots:
   virtual void handleTableViewClick(const QModelIndex& index);

signals:

protected:
    DbManager *m_db;
};

#endif // SHOWMEASUREMENTWIDGET_H
