#include "addindividualwidget.h"
#include "ui_addindividualwidget.h"
#include "ui_additemwidget.h"

#include <QMessageBox>

AddIndividualWidget::AddIndividualWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    AbstractAddItemWidget(sqlTable, parent),
    ui(new Ui::AddIndividualWidget)
{
    ui->setupUi(mainui->fieldsWidget);

    m_inputsList.insert("SpeciesID", ui->speciesComboBox);
    m_inputsList.insert("MuseumID", ui->museumComboBox);
    m_inputsList.insert("Hypodigme", ui->hypodigmeComboBox);
}

AddIndividualWidget::~AddIndividualWidget()
{
    delete ui;
}



