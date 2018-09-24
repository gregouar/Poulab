#include "addmeasurementwidget.h"
#include "ui_addmeasurementwidget.h"
#include "ui_additemwidget.h"

#include "SqlTable/abstractsqltable.h"
#include "dbmanager.h"

#include <QDebug>

AddMeasurementWidget::AddMeasurementWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    AbstractAddItemWidget(sqlTable, parent),
    ui(new Ui::AddMeasurementWidget)
{
    ui->setupUi(mainui->fieldsWidget);

    m_inputsList.insert("Value", ui->valueLineEdit);
    m_inputsList.insert("MeasurementTypeID", ui->measurementTypeComboBox);
    m_inputsList.insert("MaterialID", ui->materialComboBox);

    connect(ui->materialComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(materialChanged(int)));
    connect(this, SIGNAL(datumSet(int)), this, SLOT(materialChanged(int)));
    connect(ui->measurementTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(measurementTypeChanged(int)));

    m_disableMeasurementTypeChange = false;
}

AddMeasurementWidget::~AddMeasurementWidget()
{
    delete ui;
}


void AddMeasurementWidget::setDatum(const SqlDatum &datum)
{
    m_disableMeasurementTypeChange = true;
    AbstractAddItemWidget::setDatum(datum);
    m_disableMeasurementTypeChange = false;
}

void AddMeasurementWidget::materialChanged(int)
{
    QVariant materialID = ui->materialComboBox->currentData(Qt::UserRole);

    DbManager *db = m_sqlTable->getParentDb();

    SqlDatum materialDatum = db->getDatumFromId("Material",materialID.toInt());
    QVariant materialTypeID = materialDatum.getFieldValue("MaterialTypeID");

    const SqlField *f = m_sqlTable->getSqlField("MeasurementTypeID");

    QString filter = "MaterialTypeID IN isSubMaterialType";

    QString with = "RECURSIVE "
             "isSubMaterialType(n) AS ( "
             "VALUES("+materialTypeID.toString()+") "
             "UNION "
             "SELECT ID FROM MaterialType, isSubMaterialType "
             "WHERE ParentMaterialTypeID=isSubMaterialType.n "
            ") ";

    AbstractSqlListModel *lm = db->getListModel(QuickSqlQuery(f->linkName(), filter, with));
    if(lm != nullptr)
    {
        lm->enableNoChoice(!f->notNull());
        ui->measurementTypeComboBox->setModel(lm);

        /** FIND CURRENT SELECTED **/
        if(m_curDatum.getID() != -1 && m_curDatum.getFieldValue("MaterialID") == materialID)
        {
            QComboBox *cBox = ui->measurementTypeComboBox;

            qInfo()<<m_curDatum.getFieldValue("MeasurementTypeID");
            cBox->setCurrentIndex(cBox->findData(m_curDatum.getFieldValue("MeasurementTypeID")));
        }
    }

}


void AddMeasurementWidget::measurementTypeChanged(int)
{
    if(!m_disableMeasurementTypeChange){
    SqlDatum d = m_sqlTable->getFirstMatchDatum("MaterialID="+ui->materialComboBox->currentData(Qt::UserRole).toString()
                                                +" AND MeasurementTypeID="+ui->measurementTypeComboBox->currentData(Qt::UserRole).toString());

    //setDatum(d);

    m_curDatum = d;
    ui->valueLineEdit->setText(m_curDatum.getFieldValue("Value").toString());
    }


    DbManager *db = m_sqlTable->getParentDb();
    int measurementTypeID = ui->measurementTypeComboBox->currentData(Qt::UserRole).toInt();
    SqlDatum measurementTypeDatum = db->getDatumFromId("MeasurementType", measurementTypeID);

    QDir dir = m_sqlTable->getParentDb()->getDirectory();
    m_img.load(dir.absoluteFilePath(measurementTypeDatum.getFieldValue("Picture").toString()));

    ui->pictureLabel->setPixmap(m_img.scaled(ui->pictureLabel->geometry().width(),
                                             ui->pictureLabel->geometry().height(),
                                             Qt::KeepAspectRatio));

    ui->commentsLabel->setText(measurementTypeDatum.getFieldValue("Comments").toString());
}





