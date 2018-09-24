#include "addmeasurementtypewidget.h"
#include "ui_addmeasurementtypewidget.h"
#include "ui_additemwidget.h"

#include "SqlTable/abstractsqltable.h"
#include "dbmanager.h"

#include <QFileDialog>
#include <QImageReader>

#include <QDebug>

AddMeasurementTypeWidget::AddMeasurementTypeWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    AbstractAddItemWidget(sqlTable, parent),
    ui(new Ui::AddMeasurementTypeWidget)
{
    ui->setupUi(mainui->fieldsWidget);

    m_inputsList.insert("Name", ui->nameLineEdit);
    m_inputsList.insert("MaterialTypeID", ui->materialComboBox);
    m_inputsList.insert("Comments", ui->commentsLineEdit);
    m_inputsList.insert("Picture", ui->pictureLineEdit);

    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browsePicture()));
    ui->pictureLineEdit->setDisabled(true);

    connect(this, SIGNAL(datumSet(int)), this, SLOT(updatePicture()));
}

AddMeasurementTypeWidget::~AddMeasurementTypeWidget()
{
    delete ui;
}



void AddMeasurementTypeWidget::browsePicture()
{
    QString picture_name = QFileDialog::getOpenFileName(nullptr, tr("Choose picture"),
                               "./",
                               tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    QDir dir = m_sqlTable->getParentDb()->getDirectory();

    picture_name = dir.relativeFilePath(picture_name);

    if(!picture_name.isEmpty())
    {
        ui->pictureLineEdit->setText(picture_name);
        this->updatePicture();
    }
}

void AddMeasurementTypeWidget::updatePicture(int)
{
    QString picture_name = ui->pictureLineEdit->text();

    QDir dir = m_sqlTable->getParentDb()->getDirectory();
    m_img.load(dir.absoluteFilePath(picture_name));
    if (m_img.isNull()) {
        /* error */
        ui->pictureLabel->setPixmap(QPixmap());
    } else
    ui->pictureLabel->setPixmap(m_img.scaled(ui->pictureLabel->geometry().width(),
                                             ui->pictureLabel->geometry().height(),
                                             Qt::KeepAspectRatio));
}

