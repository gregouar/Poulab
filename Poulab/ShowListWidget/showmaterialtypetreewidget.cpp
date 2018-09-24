#include "showmaterialtypetreewidget.h"
#include "ui_showmaterialtypetreewidget.h"


ShowMaterialTypeTreeWidget::ShowMaterialTypeTreeWidget(QWidget *parent) : QWidget(parent),
    ui(new Ui::ShowMaterialTypeTreeWidget)
{
    ui->setupUi(this);

    m_selectedID = -1;

    connect(ui->addNewItem, SIGNAL(clicked()), this, SIGNAL(askToAddItem()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(editButtonClicked()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SIGNAL(askToSearchInside()));

    ui->editButton->setEnabled(false);

    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleTableViewClick()));
    connect(ui->treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(handleTableViewDoubleClick(QModelIndex)));
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openButtonClicked()));
}

ShowMaterialTypeTreeWidget::~ShowMaterialTypeTreeWidget()
{
    delete ui;
}

void ShowMaterialTypeTreeWidget::setTreeModel(AbstractSqlTreeModel *model)
{
    model->enableNoChoice(false);
    ui->treeView->setModel(model);
    ui->treeView->show();

    ui->treeView->expandAll();

    ui->nbrMatches->setText(QVariant(model->rowCount()).toString());
    ui->editButton->setEnabled(false);
    ui->openButton->setEnabled(false);

    m_explorable = true;
}


void ShowMaterialTypeTreeWidget::setTitle(const QString &title)
{
    ui->title->setText(title);
}


void ShowMaterialTypeTreeWidget::editButtonClicked()
{
    emit askToEditItem(m_selectedID);
}

void ShowMaterialTypeTreeWidget::openButtonClicked()
{
    emit askToExploreItem(ui->treeView->model()->data(ui->treeView->currentIndex(), Qt::UserRole).toInt());
}


void ShowMaterialTypeTreeWidget::handleTableViewClick()
{
    m_selectedID = ui->treeView->model()->data(ui->treeView->currentIndex(), Qt::UserRole).toInt();

    ui->editButton->setEnabled(true);

    if(m_explorable)
        ui->openButton->setEnabled(true);
}


void ShowMaterialTypeTreeWidget::handleTableViewDoubleClick(const QModelIndex& index)
{
    if(m_explorable)
        emit askToExploreItem(ui->treeView->model()->data(index, Qt::UserRole).toInt());
    else
        emit askToEditItem(ui->treeView->model()->data(index, Qt::UserRole).toInt());
}


