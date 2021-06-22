#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

#include "AddItemWidget/addmuseumwidget.h"
#include "AddItemWidget/addspecieswidget.h"
#include "AddItemWidget/addmaterialtypewidget.h"
#include "AddItemWidget/addmeasurementtypewidget.h"
#include "AddItemWidget/addindividualwidget.h"
#include "AddItemWidget/addmaterialwidget.h"
#include "AddItemWidget/addmeasurementwidget.h"


#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    ui->setupUi(this);

    m_curParentID = -1;

    m_mainMenu = new MainMenuWidget();
    ui->mainLayout->addWidget(m_mainMenu);

    m_showListWidget = new ShowListWidget();
    ui->mainLayout->addWidget(m_showListWidget);

    m_showMeasurementWidget = new ShowMeasurementWidget();
    ui->mainLayout->addWidget(m_showMeasurementWidget);

    m_showMeasurementTypeWidget = new ShowMeasurementTypeWidget(&m_dbManager);
    ui->mainLayout->addWidget(m_showMeasurementTypeWidget);

    m_showMaterialTypeTreeWidget = new ShowMaterialTypeTreeWidget();
    ui->mainLayout->addWidget(m_showMaterialTypeTreeWidget);

    m_statisticsWidget = new StatisticsWidget();
    ui->mainLayout->addWidget(m_statisticsWidget);

    m_searchWidget = new SearchWidget(&m_dbManager);
    ui->mainLayout->addWidget(m_searchWidget);

    this->addAddItemWidget("Museum",new AddMuseumWidget(m_dbManager.getTable("Museum")));
    this->addAddItemWidget("Species",new AddSpeciesWidget(m_dbManager.getTable("Species")));
    this->addAddItemWidget("MaterialType",new AddMaterialTypeWidget(m_dbManager.getTable("MaterialType")));
    this->addAddItemWidget("MeasurementType",new AddMeasurementTypeWidget(m_dbManager.getTable("MeasurementType")));
    this->addAddItemWidget("Individual",new AddIndividualWidget(m_dbManager.getTable("Individual")));
    this->addAddItemWidget("Material",new AddMaterialWidget(m_dbManager.getTable("Material")));
    this->addAddItemWidget("Measurement",new AddMeasurementWidget(m_dbManager.getTable("Measurement")));


    QMap<QString, AbstractAddItemWidget*>::iterator i;
    for( i = m_addItemWidgetList.begin() ; i != m_addItemWidgetList.end() ; ++i )
    {
        connect(i.value(), SIGNAL(itemAdded()), this, SLOT(showBack()));
        connect(i.value(), SIGNAL(itemDeleted()), this, SLOT(showBack()));
        connect(i.value(), SIGNAL(cancel()), this, SLOT(showBack()));
    }

    m_addAllMeasurementsWidget = new AddAllMeasurementsWidget(m_dbManager.getTable("Measurement"));
    ui->mainLayout->addWidget(m_addAllMeasurementsWidget);

    connect(m_addAllMeasurementsWidget, SIGNAL(itemAdded()), this, SLOT(showBack()));
    connect(m_addAllMeasurementsWidget, SIGNAL(cancel()), this, SLOT(showBack()));


    connect(m_showListWidget, SIGNAL(askToAddItem()), this, SLOT (showAddItem()));
    connect(m_showListWidget, SIGNAL(askToEditItem(int)), this, SLOT (showAddItem(int)));
    connect(m_showListWidget, SIGNAL(askToExploreItem(int)), this, SLOT(exploreItem(int)));
    connect(m_showListWidget, SIGNAL(askToSearchInside()), this, SLOT(searchInsideCurTable()));

    connect(m_showMeasurementWidget, SIGNAL(askToAddItem()), this, SLOT (showAddItem()));
    connect(m_showMeasurementWidget, SIGNAL(askToEditItem(int)), this, SLOT (showAddItem(int)));
    connect(m_showMeasurementWidget, SIGNAL(askToAddAllMeasurements()), this, SLOT(showAddAllMeasurements()));
    connect(m_showMeasurementWidget, SIGNAL(askToSearchInside()), this, SLOT(searchInsideCurTable()));


    connect(m_showMeasurementTypeWidget, SIGNAL(askToAddItem()), this, SLOT (showAddItem()));
    connect(m_showMeasurementTypeWidget, SIGNAL(askToEditItem(int)), this, SLOT (showAddItem(int)));
    connect(m_showMeasurementTypeWidget, SIGNAL(askToSearchInside()), this, SLOT(searchInsideCurTable()));

    connect(m_showMaterialTypeTreeWidget, SIGNAL(askToAddItem()), this, SLOT (showAddItem()));
    connect(m_showMaterialTypeTreeWidget, SIGNAL(askToEditItem(int)), this, SLOT (showAddItem(int)));
    connect(m_showMaterialTypeTreeWidget, SIGNAL(askToExploreItem(int)), this, SLOT(exploreItem(int)));
    connect(m_showMaterialTypeTreeWidget, SIGNAL(askToSearchInside()), this, SLOT(searchInsideCurTable()));

    connect(ui->mainMenuButton, SIGNAL(clicked()), this, SLOT(showMainMenu()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(showBack()));

    connect(m_mainMenu, SIGNAL(askToShowStatisticsWidget()), this, SLOT(showStatisticsWidget()));
    connect(m_mainMenu, SIGNAL(askToShowSearchWidget()), this, SLOT(showSearchWidget()));
    connect(m_mainMenu, SIGNAL (askToShowList(const QString &)), this, SLOT (showSearchList(const QString &)));
    connect(m_mainMenu, SIGNAL (askToShowMaterialTypeTree()), this, SLOT (showMaterialTypeTree()));

    connect(m_searchWidget, SIGNAL(askToSearch(QuickSqlQuery)), this, SLOT(showSearchList(QuickSqlQuery)));

    connect(ui->actionNew_database, SIGNAL (triggered()), &m_dbManager, SLOT (createDb()));
    connect(ui->actionOpen_database, SIGNAL (triggered()), &m_dbManager, SLOT (openDb()));
    connect(ui->actionSave_database_as, SIGNAL(triggered()), &m_dbManager, SLOT(saveDbAs()));
    connect(ui->actionClose_database, SIGNAL (triggered()), &m_dbManager, SLOT (closeDb()));
    connect(ui->actionExit, SIGNAL (triggered()), QApplication::instance(), SLOT (quit()));

    m_actionAddItemMapper = new QSignalMapper(this);
    connect(m_actionAddItemMapper, SIGNAL(mapped(QString)), this, SLOT(showAddItem(QString)));

    connect(ui->actionMuseum, SIGNAL(triggered()), m_actionAddItemMapper, SLOT(map()));
    connect(ui->actionSpecies, SIGNAL(triggered()), m_actionAddItemMapper, SLOT(map()));
    connect(ui->actionIndividual, SIGNAL(triggered()), m_actionAddItemMapper, SLOT(map()));
    connect(ui->actionMaterial, SIGNAL(triggered()), m_actionAddItemMapper, SLOT(map()));
    connect(ui->actionMaterialType, SIGNAL(triggered()), m_actionAddItemMapper, SLOT(map()));
    connect(ui->actionMeasurementType, SIGNAL(triggered()), m_actionAddItemMapper, SLOT(map()));
    m_actionAddItemMapper->setMapping(ui->actionMuseum, "Museum");
    m_actionAddItemMapper->setMapping(ui->actionSpecies, "Species");
    m_actionAddItemMapper->setMapping(ui->actionIndividual, "Individual");
    m_actionAddItemMapper->setMapping(ui->actionMaterial, "Material");
    m_actionAddItemMapper->setMapping(ui->actionMaterialType, "MaterialType");
    m_actionAddItemMapper->setMapping(ui->actionMeasurementType, "MeasurementType");

    m_execQueryDialog = new LineEditDialog("Execute query",
                                           "Executing a custom sql query can cause severe, irreversible damages to the database.\n"
                                           "Please be careful.");

    connect(ui->actionSearch_for, SIGNAL (triggered()), this, SLOT (showSearchWidget()));
    connect(ui->actionExecute_query, SIGNAL(triggered()), m_execQueryDialog,  SLOT(show()));
    connect(m_execQueryDialog, SIGNAL(accepted()), this, SLOT (executeQuery()));

    connect(&m_dbManager, SIGNAL (connected(bool)), this, SLOT (connectedToDb(bool)));

    disableEverything();
}


void MainWindow::addAddItemWidget(const QString tableName, AbstractAddItemWidget* widget)
{
    m_addItemWidgetList.insert(tableName,widget);
    ui->mainLayout->addWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMainMenu()
{
    this->hideEverything();
    m_mainMenu->show();
    m_curTableName = "";
    m_curParentID = -1;
    m_curParentTableName = "";

    this->addToHistory(WIDGET_MAINMENU);
}

void MainWindow::showSearchList(const QuickSqlQuery& quickquery)
{
    this->hideEverything();

    ShowListWidget *showWidget = m_showListWidget;

    if(quickquery.tableName() == "Measurement" && m_curParentID != -1)
        showWidget = m_showMeasurementWidget;
    else if(quickquery.tableName() == "MeasurementType")
        showWidget = m_showMeasurementTypeWidget;

    showWidget->show();

    if(!quickquery.tableName().isEmpty())
    {
        m_curParentTableName = m_curTableName;
        m_curTableName = quickquery.tableName();
    }

    if(!m_curTableName.isEmpty())
    {
        QString title = "List of "+m_curTableName+"s";

        if(m_curParentID != -1 && !m_curParentTableName.isEmpty())
             title += " in "+m_dbManager.getItemListName(m_curParentTableName, m_curParentID);

        showWidget->setTableModel(m_dbManager.getTableModel(quickquery),
                                 !m_dbManager.getTable(quickquery.tableName())->getMainChild().isEmpty());

        showWidget->setTitle(title);

        /// CHECK THIS ///
        this->addToHistory(WIDGET_SHOWLIST, quickquery.tableName(), m_curParentID);
    } else
        showMainMenu();
}

void MainWindow::showSearchList(const QString &tableName, int parentID)
{
    if(!tableName.isEmpty())
    {
        m_curParentID = parentID;
        QString filter;
        if(m_curParentID != -1 && !m_curTableName.isEmpty())
        {
            const QString &parentLinkField =
                    m_dbManager.searchParentLinkFieldName(tableName, m_curTableName);

            filter = "  "+parentLinkField+" = "+QVariant(m_curParentID).toString()+" ";
        }

        this->showSearchList(QuickSqlQuery(tableName,filter));
    }
}

void MainWindow::showMaterialTypeTree()
{
    this->hideEverything();

    m_showMaterialTypeTreeWidget->show();

    m_curTableName = "MaterialType";
    m_curParentID = -1;

    m_dbManager.readTable(m_curTableName);
    m_showMaterialTypeTreeWidget->setTreeModel(m_dbManager.getTreeModel(m_curTableName));
    this->addToHistory(WIDGET_MATERIALTYPETREE);
}

void MainWindow::exploreItem(int ID)
{
    QString oldTableName = m_curTableName;
    const AbstractSqlTable* t =  m_dbManager.getTable(m_curTableName);

    if(t != nullptr)
    {
        const QString &mc = t->getMainChild();
        if(!mc.isEmpty())
            showSearchList(mc, ID);
        m_historyStack.pop_back();
        this->addToHistory(EXPLORE_ITEM, oldTableName, ID);
    }
}


void MainWindow::showAddItem(int ID)
{
    showAddItem(m_curTableName, ID);
}

void MainWindow::showAddItem(const QString &tableName, int ID)
{
    QMap<QString, AbstractAddItemWidget*>::iterator  i = m_addItemWidgetList.find(tableName);
    if(i != m_addItemWidgetList.end())
    {
        m_curTableName = tableName;

        this->hideEverything();
        i.value()->show();

        i.value()->setDatum(m_dbManager.getDatumFromId(m_curTableName, ID));

        const QString &parentLinkField =
                m_dbManager.searchParentLinkFieldName(m_curTableName, m_curParentTableName);

        i.value()->setParentDefaultChoice(parentLinkField, m_curParentID);

        this->addToHistory(WIDGET_ADDITEM, tableName, ID);
    }
    else
    {/*deal with error*/}
}

void MainWindow::showAddAllMeasurements()
{
    if(m_curParentTableName == "Material" && m_curParentID != -1)
    {
        m_curTableName = "Measurement";
        this->hideEverything();
        m_addAllMeasurementsWidget->show();
        m_addAllMeasurementsWidget->setParentMaterial(m_curParentID);
        this->addToHistory(WIDGET_ADDITEM, m_curTableName,-1);
    }
}

void MainWindow::showStatisticsWidget()
{
    this->hideEverything();
    m_statisticsWidget->show();
    m_statisticsWidget->updateStatistics(&m_dbManager);
    this->addToHistory(WIDGET_STATISTICS);
}

void MainWindow::showSearchWidget()
{
    this->hideEverything();
    m_searchWidget->show();
    this->addToHistory(WIDGET_SEARCH);
}

void MainWindow::searchInsideCurTable()
{
    this->showSearchWidget();
    m_searchWidget->setCurTable(m_curTableName);

    const QString &parentLinkField =
            m_dbManager.searchParentLinkFieldName(m_curTableName, m_curParentTableName);

    if(!parentLinkField.isEmpty())
        m_searchWidget->addFilter(parentLinkField,m_curParentID);
}


void MainWindow::addToHistory(WIDGET_NAME name, const QString &text, int value)
{
    HistoryAction h;
    h.name = name;
    h.text = text;
    h.value = value;

    bool add = true;
    if(!m_historyStack.isEmpty())
    if(m_historyStack.back().name == h.name)
    if(m_historyStack.back().value == h.value)
    if(m_historyStack.back().text == h.text)
        add = false;

    if(add)
       m_historyStack.push_back(h);

    ui->backButton->setEnabled(m_historyStack.size() > 1);
}

void MainWindow::showBack()
{
    if(m_historyStack.size() > 1)
    {
        m_historyStack.pop_back();
        HistoryAction h = m_historyStack.back();

        int old_stackSize = m_historyStack.size();

        if(h.name == WIDGET_MAINMENU)
            this->showMainMenu();
        else if(h.name == WIDGET_SHOWLIST)
            this->showSearchList(h.text, h.value);
        else if(h.name == WIDGET_ADDITEM)
            this->showAddItem(h.text, h.value);
        else if(h.name == WIDGET_STATISTICS)
            this->showStatisticsWidget();
        else if(h.name == WIDGET_SEARCH)
            this->showSearchWidget();
        else if(h.name == EXPLORE_ITEM)
        {
            m_curTableName = h.text;
            this->exploreItem(h.value);
        } else if(h.name == WIDGET_MATERIALTYPETREE)
            this->showMaterialTypeTree();

        if(m_historyStack.size() != old_stackSize)
            m_historyStack.pop();
    }

    if(m_historyStack.size() <= 1)
        ui->backButton->setEnabled(false);
}

void MainWindow::executeQuery()
{
    QString query_txt = m_execQueryDialog->value();
    if(!query_txt.isEmpty())
    {
        if(!m_dbManager.executeQuery(query_txt))
        {
            QMessageBox::critical(nullptr, QObject::tr("Cannot execute query"),
                QObject::tr("Invalid sql query.\n\n"
                            "Click Ok to try again."), QMessageBox::Ok);
            m_execQueryDialog->show();
        } else
            m_execQueryDialog->setValue("");
    }
}

void MainWindow::hideEverything()
{
    m_mainMenu->hide();
    m_showListWidget->hide();
    m_showMeasurementWidget->hide();
    m_showMeasurementTypeWidget->hide();
    m_showMaterialTypeTreeWidget->hide();
    m_statisticsWidget->hide();
    m_searchWidget->hide();

    QMap<QString, AbstractAddItemWidget*>::iterator i;
    for( i = m_addItemWidgetList.begin() ; i != m_addItemWidgetList.end() ; ++i )
        i.value()->hide();

    m_addAllMeasurementsWidget->hide();
}

void MainWindow::disableEverything()
{
    showMainMenu();
    m_mainMenu->setEnabled(false);
    ui->menuSearch->setEnabled(false);
    ui->menuAdd->setEnabled(false);
    ui->menuSql->setEnabled(false);
    ui->actionSave_database_as->setEnabled(false);
    ui->backButton->setEnabled(false);
}

void MainWindow::restart()
{  
    m_historyStack = QStack<HistoryAction> ();
    showMainMenu();
    m_mainMenu->setEnabled(true);
    ui->menuSearch->setEnabled(true);
    ui->menuAdd->setEnabled(true);
    ui->menuSql->setEnabled(true);
    ui->actionSave_database_as->setEnabled(true);
    ui->backButton->setEnabled(false);
}

void MainWindow::connectedToDb(bool b)
{
    if(b == true)
        restart();
    else
        disableEverything();
}



