#include "addmuseumwidget.h"
#include "ui_addmuseumwidget.h"
#include "ui_additemwidget.h"

AddMuseumWidget::AddMuseumWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    AbstractAddItemWidget(sqlTable, parent),
    ui(new Ui::AddMuseumWidget)
{
    ui->setupUi(mainui->fieldsWidget);

    m_inputsList.insert("Name", ui->nameLineEdit);
    m_inputsList.insert("Country", ui->countryLineEdit);
}

AddMuseumWidget::~AddMuseumWidget()
{
    delete ui;
}

