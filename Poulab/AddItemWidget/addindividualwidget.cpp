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
    m_inputsList.insert("InventoryNumber", ui->inventoryNumberLineEdit);
    m_inputsList.insert("Maturity", ui->maturityComboBox);
    m_inputsList.insert("Thanatocoenosis", ui->thanatoComboBox);
}

AddIndividualWidget::~AddIndividualWidget()
{
    delete ui;
}



