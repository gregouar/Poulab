#include "showlistwidget.h"
#include "ui_showlistwidget.h"


ShowListWidget::ShowListWidget(QWidget *parent) : QWidget(parent),
    ui(new Ui::ShowListWidget)
{
    ui->setupUi(this);

    ui->tableView->setSortingEnabled(true);

    m_selectedID = -1;

    connect(ui->addNewItem, SIGNAL(clicked()), this, SIGNAL(askToAddItem()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(editButtonClicked()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SIGNAL(askToSearchInside()));

    ui->editButton->setEnabled(false);

    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleTableViewClick(QModelIndex)));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(handleTableViewDoubleClick(QModelIndex)));
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openButtonClicked()));

    ui->openButton->setShortcut(QKeySequence(Qt::Key_Enter));
    ui->openButton->grabShortcut(QKeySequence(Qt::Key_Enter),Qt::ApplicationShortcut );

    m_sortingProxy = new QSortFilterProxyModel(this);
}

ShowListWidget::~ShowListWidget()
{
    delete ui;
}

void ShowListWidget::setTableModel(QAbstractItemModel *model, bool explorable)
{
    m_sortingProxy->setSourceModel(model);
    ui->tableView->setModel(m_sortingProxy);
    ui->tableView->show();

    ui->nbrMatches->setText("Number of matches: "+QVariant(model->rowCount()).toString());
    ui->editButton->setEnabled(false);
    ui->openButton->setEnabled(false);

    m_explorable = explorable;
}


void ShowListWidget::setTitle(const QString &title)
{
    ui->title->setText(title);
}


void ShowListWidget::editButtonClicked()
{
    emit askToEditItem(m_selectedID);
}

void ShowListWidget::openButtonClicked()
{
    emit askToExploreItem(ui->tableView->model()->data(ui->tableView->currentIndex(), Qt::UserRole).toInt());
}


void ShowListWidget::handleTableViewClick(const QModelIndex& index)
{
    int row = index.row();
    m_selectedID = index.sibling(row, 0).data().toInt();

    ui->editButton->setEnabled(true);

    if(m_explorable)
        ui->openButton->setEnabled(true);
}


void ShowListWidget::handleTableViewDoubleClick(const QModelIndex& index)
{
    if(m_explorable)
        emit askToExploreItem(ui->tableView->model()->data(index, Qt::UserRole).toInt());
    else
        emit askToEditItem(ui->tableView->model()->data(index, Qt::UserRole).toInt());
}


