#include "addmaterialtypewidget.h"
#include "ui_addmaterialtypewidget.h"
#include "ui_additemwidget.h"

#include <QMessageBox>

AddMaterialTypeWidget::AddMaterialTypeWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    AbstractAddItemWidget(sqlTable, parent),
    ui(new Ui::AddMaterialTypeWidget)
{
    ui->setupUi(mainui->fieldsWidget);

    m_inputsList.insert("Name", ui->nameLineEdit);
    m_inputsList.insert("ParentMaterialTypeID", ui->parentMaterialComboBox);

}

AddMaterialTypeWidget::~AddMaterialTypeWidget()
{
    delete ui;
}


