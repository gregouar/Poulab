#include "addmaterialwidget.h"
#include "ui_addmaterialwidget.h"
#include "ui_additemwidget.h"


AddMaterialWidget::AddMaterialWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    AbstractAddItemWidget(sqlTable, parent),
    ui(new Ui::AddMaterialWidget)
{
    ui->setupUi(mainui->fieldsWidget);

    m_inputsList.insert("InventoryNumber", ui->inventoryNumberLineEdit);
    m_inputsList.insert("MaterialTypeID", ui->materialComboBox);
    m_inputsList.insert("IndividualID", ui->individualComboBox);
    m_inputsList.insert("Parity", ui->parityComboBox);
    m_inputsList.insert("Completeness", ui->completenessComboBox);
    m_inputsList.insert("Comments", ui->commentsLineEdit);
}

AddMaterialWidget::~AddMaterialWidget()
{
    delete ui;
}
