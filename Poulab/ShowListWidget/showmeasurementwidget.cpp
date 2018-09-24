#include "showmeasurementwidget.h"
#include "ui_showlistwidget.h"

ShowMeasurementWidget::ShowMeasurementWidget(QWidget *parent) :
    ShowListWidget(parent)
{
    ui->openButton->setText("Add all measurements");
}

ShowMeasurementWidget::~ShowMeasurementWidget()
{

}

void ShowMeasurementWidget::setTableModel(QAbstractItemModel *model, bool explorable)
{
    ShowListWidget::setTableModel(model, explorable);
    ui->openButton->setEnabled(true);
}


void ShowMeasurementWidget::openButtonClicked()
{
    emit askToAddAllMeasurements();
}
