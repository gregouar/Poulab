
#include "showmeasurementtypewidget.h"
#include "ui_showlistwidget.h"

#include "copymeasurementtypedialog.h"

#include <QAbstractItemModel>
#include <QMessageBox>

#include<QDebug>

ShowMeasurementTypeWidget::ShowMeasurementTypeWidget(DbManager *db, QWidget *parent) :
    ShowListWidget(parent)
{
    ui->openButton->setText("Copy to");
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setDragDropMode(QAbstractItemView::InternalMove);
    ui->tableView->setDragEnabled(true);
    ui->tableView->setAcceptDrops(true);
    ui->tableView->setDropIndicatorShown(true);
    ui->tableView->setSortingEnabled(false);
    m_db = db;
}

ShowMeasurementTypeWidget::~ShowMeasurementTypeWidget()
{

}

void ShowMeasurementTypeWidget::handleTableViewClick(const QModelIndex& index)
{
    ShowListWidget::handleTableViewClick(index);
    ui->openButton->setEnabled(true);
}


void ShowMeasurementTypeWidget::openButtonClicked()
{
    AbstractSqlTreeModel *model = m_db->getTreeModel(QuickSqlQuery("MaterialType"));
    CopyMeasurementTypeDialog *diag = new CopyMeasurementTypeDialog(model);

    if (diag->exec() == QDialog::Accepted)
    {
        QModelIndexList sl = ui->tableView->selectionModel()->selectedRows();
        int target_mat_id = diag->chosenData(Qt::UserRole).toInt();
        SqlDatum mat_datum = m_db->getDatumFromId("MaterialType",target_mat_id);

        for (int i = 0; i < sl.size(); i++)
        {
                int source_meas_id = sl[i].data().toInt();
                SqlDatum d = m_db->getDatumFromId("MeasurementType",source_meas_id);

                QString filter = "MaterialTypeID="+QVariant(target_mat_id).toString()
                           +" AND Name='"+d.getFieldValue("Name").toString()+"'";
                SqlDatum match = m_db->getFirstMatchDatum("MeasurementType",filter);

                bool add = true;

                if(match.isValid() && match.getID() != -1)
                {
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(this, "Copy item", "There is already a MeasurementType named '"+d.getFieldValue("Name").toString()+"' "
                                                                     "associated to the MaterialType '"+mat_datum.getFieldValue("Name").toString()+"'.\n"
                                                                     "Are you sure you want to add a new one with the same name ?",
                                                  QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::No) {
                        add = false;
                    }
                }
                d.setFieldValue("MaterialTypeID",target_mat_id);
                if(add == true)
                    d.addToTableAs(-1);
        }
    }

    delete diag;
}

