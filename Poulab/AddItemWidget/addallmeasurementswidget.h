/** This special kind of add widget will show the full list of MeasurementType
 * that can be added to a corresponding Material.
**/

#ifndef ADDALLMEASUREMENTSWIDGET_H
#define ADDALLMEASUREMENTSWIDGET_H

#include <QWidget>
#include <QSignalMapper>

#include "SqlDatum/sqldatum.h"
#include "ListModel/abstractsqllistmodel.h"


namespace Ui {
class AddAllMeasurementsWidget;
}

class AddAllMeasurementsWidget : public QWidget
{

    Q_OBJECT
public:
    explicit AddAllMeasurementsWidget(const AbstractSqlTable *sqlTable, QWidget *parent = nullptr);
    virtual ~AddAllMeasurementsWidget();

    void setParentMaterial(int ID);


signals:
    void itemAdded();
    void cancel();

public slots:
    virtual void addItem();

protected slots:
    virtual void updatePicture(int measurementTypeID);

protected:
    void cleanFieldsList();
    void generateSqlList(int parentID);
    void generateInputFields(int parentID);

    const AbstractSqlTable *m_sqlTable;

    AbstractSqlListModel* m_sqlList;
    QMap<int, QWidget*> m_fieldsList;
    QMap<QWidget*, SqlDatum> m_sqlDatumList;

    Ui::AddAllMeasurementsWidget *mainui;
    QSignalMapper *m_signalMapper;
    QPixmap m_img;
};

#endif // ADDALLMEASUREMENTSWIDGET_H

