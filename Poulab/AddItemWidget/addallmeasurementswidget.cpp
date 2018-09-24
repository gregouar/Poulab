#include "addallmeasurementswidget.h"
#include "ui_addallmeasurementswidget.h"
#include "SqlTable/abstractsqltable.h"
#include "dbmanager.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>

#include <QTreeView>

#include <QDebug>

AddAllMeasurementsWidget::AddAllMeasurementsWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    QWidget(parent),
    mainui(new Ui::AddAllMeasurementsWidget)
{
    m_signalMapper = new QSignalMapper(this);

    m_sqlTable = sqlTable;

    mainui->setupUi(this);

    connect(mainui->addItemButton, SIGNAL (clicked()), this, SLOT (addItem()));
    connect(mainui->cancelButton, SIGNAL (clicked()), this, SIGNAL (cancel()));

    mainui->addItemButton->setShortcut(QKeySequence(Qt::Key_Enter));

    connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(updatePicture(int)));
}

AddAllMeasurementsWidget::~AddAllMeasurementsWidget()
{
    delete mainui;
}

void AddAllMeasurementsWidget::setParentMaterial(int ID)
{
    this->generateSqlList(ID);
    this->generateInputFields(ID);
    mainui->commentsLabel->setText("Click 'Details' for more informations about the MeasurementType.");
    mainui->pictureLabel->setPixmap(QPixmap ());
}


void AddAllMeasurementsWidget::addItem()
{
    QMap<int,QWidget*>::iterator i;
    for(i = m_fieldsList.begin() ; i != m_fieldsList.end() ; ++i)
    {
        QLineEdit* lineEdit = (QLineEdit*)i.value();
        QString value = lineEdit->text();

        if(!value.isEmpty())
        {
            SqlDatum *d = &m_sqlDatumList[i.value()];
            d->setFieldValue("MeasurementTypeID", i.key());
            d->setFieldValue("Value",value);
            d->addToTable();
        }
    }

    emit itemAdded();
}


void AddAllMeasurementsWidget::cleanFieldsList()
{
    while(mainui->formLayout->rowCount() > 0)
        mainui->formLayout->removeRow(0);
    m_fieldsList.clear();
    m_sqlDatumList.clear();
}

void AddAllMeasurementsWidget::generateSqlList(int parentID)
{
    QVariant materialID = parentID;

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

    m_sqlList = db->getListModel(QuickSqlQuery(f->linkName(), filter, with));
}

void AddAllMeasurementsWidget::generateInputFields(int parentID)
{
    cleanFieldsList();

    int rc = m_sqlList->rowCount();

    for(int i = 0 ; i < rc ; ++i)
    {
        QModelIndex index = m_sqlList->index(i,0);
        QVariant name_data = m_sqlList->data(index);
        int id_data = m_sqlList->data(index, Qt::UserRole).toInt();

        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setToolTip(m_sqlList->data(index, Qt::ToolTipRole).toString());

        QHBoxLayout* hbox = new QHBoxLayout();
        QPushButton* pushb = new QPushButton("Details");

        connect(pushb, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
        m_signalMapper->setMapping(pushb, id_data);

        hbox->addWidget(lineEdit);
        hbox->addWidget(pushb);

        mainui->formLayout->addRow(name_data.toString(), hbox);

        SqlDatum match = m_sqlTable->getFirstMatchDatum("MaterialID="+QVariant(parentID).toString()
                                                        +" AND MeasurementTypeID="+QVariant(id_data).toString());

        if(match.isValid())
        {
            lineEdit->setText(match.getFieldValue("Value").toString());
        } else
        {
            match = SqlDatum(m_sqlTable, -1);
            match.setFieldValue("MaterialID", parentID);
            match.setFieldValue("MeasurementTypeID", id_data);
        }


        m_fieldsList.insert(id_data,lineEdit);
        m_sqlDatumList.insert(lineEdit, match);
    }
}

void AddAllMeasurementsWidget::updatePicture(int measurementTypeID)
{
    DbManager *db = m_sqlTable->getParentDb();
    SqlDatum measurementTypeDatum = db->getDatumFromId("MeasurementType", measurementTypeID);


    QDir dir = m_sqlTable->getParentDb()->getDirectory();
    m_img.load(dir.absoluteFilePath(measurementTypeDatum.getFieldValue("Picture").toString()));

    mainui->pictureLabel->setPixmap(m_img.scaled(mainui->pictureLabel->geometry().width(),
                                             mainui->pictureLabel->geometry().height(),
                                             Qt::KeepAspectRatio));

    mainui->commentsLabel->setText(measurementTypeDatum.getFieldValue("Comments").toString());
}



