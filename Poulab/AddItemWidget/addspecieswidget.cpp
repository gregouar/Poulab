#include "addspecieswidget.h"
#include "ui_addspecieswidget.h"
#include "ui_additemwidget.h"


AddSpeciesWidget::AddSpeciesWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    AbstractAddItemWidget(sqlTable, parent),
    ui(new Ui::AddSpeciesWidget)
{
    ui->setupUi(mainui->fieldsWidget);

    m_inputsList.insert("Name", ui->nameLineEdit);
    m_inputsList.insert("Genus", ui->genusLineEdit);
    m_inputsList.insert("Subfamily", ui->subfamilyLineEdit);
    m_inputsList.insert("Family", ui->familyLineEdit);
    m_inputsList.insert("Clade", ui->cladeLineEdit);
}

AddSpeciesWidget::~AddSpeciesWidget()
{
    delete ui;
}

