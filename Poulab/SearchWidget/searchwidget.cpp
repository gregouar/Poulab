#include "searchwidget.h"
#include "ui_searchwidget.h"

#include <QClipboard>
#include <QMessageBox>

#include <QDebug>

SearchWidget::SearchWidget(DbManager *db, QWidget *parent) : QWidget(parent),
  ui(new Ui::SearchWidget)
{
    ui->setupUi(this);
    m_db = db;

    m_deleteSignalMapper = new QSignalMapper(this);
    connect(m_deleteSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(deleteFilter(QObject*)));
    connect(m_deleteSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(deleteJoin(QObject*)));

    connect(ui->tableComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(tableChanged(int)));
    connect(ui->copyClipButton, SIGNAL(clicked()), this, SLOT(copyQueryToClipboard()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(askToSearch()));

    QList<QString> tl = m_db->getTableNameList();
    for(int i = 0 ; i < tl.size() ; ++i)
        ui->tableComboBox->addItem(tl[i]);

   connect(ui->addJoinButton, SIGNAL(clicked()), this, SLOT(addJoin()));
   connect(ui->addFilterButton, SIGNAL(clicked()), this, SLOT(addFilter()));
}

SearchWidget::~SearchWidget()
{
    delete ui;
}


void SearchWidget::setCurTable(const QString &tablename)
{
    int i = ui->tableComboBox->findText(tablename);
    ui->tableComboBox->setCurrentIndex(i);
    tableChanged(i);
}

QString SearchWidget::getCurTableName()
{
    return ui->tableComboBox->currentText();
}

QPair<QString,QString> SearchWidget::searchJoinRelation(QString joinTableName)
{
    QString childTableQuery, parentTableQuery;
    bool cont = true;
    for(int j = -1 ; j < m_joinList.size() && cont ; ++j)
    {
        const AbstractSqlTable *sqltable;

        if(j == - 1)
            sqltable = m_db->getTable(this->getCurTableName());
        else
            sqltable = m_db->getTable(m_joinList[j]->joinTableName());

        QString foundedParentField = sqltable->getParentFieldName(joinTableName);
        if(!foundedParentField.isEmpty())
        {
            childTableQuery = sqltable->getTableName()+"."+foundedParentField;
            parentTableQuery = joinTableName+".ID";
            cont = false;
        } else {
            foundedParentField = m_db->getTable(joinTableName)->getParentFieldName(sqltable->getTableName());
            if(!foundedParentField.isEmpty())
            {
                childTableQuery = joinTableName+"."+foundedParentField;
                parentTableQuery = sqltable->getTableName()+".ID";
            }
        }
    }

    return QPair<QString, QString>(parentTableQuery, childTableQuery);
}

void SearchWidget::addJoin(const QString &joinTableName)
{
    QComboBox *joinCBox = new QComboBox();

    QList<QString> tl = m_db->getTableNameList();
    for(int i = 0 ; i < tl.size() ; ++i)
    {
        bool isChildOrParent = false,
             isAlreadyInJoinList = false;

        for(int j = -1 ; j < m_joinList.size() ; ++j)
        {
            const AbstractSqlTable *sqltable;

            if(j == - 1)
                sqltable = m_db->getTable(this->getCurTableName());
            else
                sqltable = m_db->getTable(m_joinList[j]->joinTableName());

            // Check if the table we want to add in the list is parent or child of a currently open table
            if(sqltable != nullptr)
            {
                if(sqltable->getTableName() == tl[i])
                    isAlreadyInJoinList = true;
                else if(!sqltable->getParentFieldName(tl[i]).isEmpty() ||
                   !m_db->getTable(tl[i])->getParentFieldName(sqltable->getTableName()).isEmpty())
                    isChildOrParent = true;
            }
        }

        if(!isAlreadyInJoinList && isChildOrParent)
            joinCBox->addItem(tl[i]);
    }

    if(joinCBox->count() > 0)
    {
        QHBoxLayout *rightLayout = new QHBoxLayout();
        QPushButton *delButton = new QPushButton("X");

        rightLayout->addStretch(1);
        rightLayout->addWidget(delButton);

        ui->joinsFormLayout->insertRow(m_joinList.size(),joinCBox/*parentCBox*/,rightLayout);
        connect(joinCBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateAllTableList()));


        QString tn = joinTableName;
        if(tn.isEmpty())
            tn = joinCBox->itemText(0);

        if(!tn.isEmpty())
        {
            JoinForm *join = new JoinForm(joinCBox,
                                          delButton,
                                          ui->joinTextEdit->addNonEditableText(" INNER JOIN "),
                                          m_db);

            if(!m_joinList.isEmpty())
                m_joinList.back()->enableEditable(false);

            connect(join, SIGNAL(askToChangeNonEditablePart(const NonEditablePart*,QString)),
                    this, SLOT(changeJoinText(const NonEditablePart*,QString)));
            connect(join, SIGNAL(askToDeleteNonEditablePart(const NonEditablePart*)),
                    this, SLOT(deleteNonEditablePartJoinText(const NonEditablePart*)));

            connect(delButton, SIGNAL(clicked()), m_deleteSignalMapper, SLOT(map()));
            m_deleteSignalMapper->setMapping(delButton, join);

            m_joinList.push_back(join);

            int index = joinCBox->findText(tn);
            joinCBox->setCurrentIndex(index);
            join->changeJoinTable(index);
        }
    } else
        delete joinCBox;

    if(joinCBox->count() < 1)
        ui->addJoinButton->setEnabled(false);

    this->updateAllTableList();
}

void SearchWidget::addFilter(const QString &fieldName, QVariant value)
{
    QComboBox *tableCBox = new QComboBox;
    tableCBox->addItems(this->getTableList());

    QHBoxLayout *innerFormLayout = new QHBoxLayout();
    QHBoxLayout *rightLayout = new QHBoxLayout();
    QPushButton *delButton = new QPushButton("X");
    rightLayout->addWidget(new QLabel("."));
    rightLayout->addLayout(innerFormLayout,4);
    rightLayout->addStretch(1);
    rightLayout->addWidget(delButton);

    ui->filtersFormLayout->insertRow(m_filterList.size(),tableCBox,rightLayout);

    FilterForm *filt = new FilterForm(tableCBox,innerFormLayout,
                                      ui->whereTextEdit->addNonEditableText(" "),
                                      ui->whereTextEdit->addNonEditableText(" "),
                                      m_db);

    if(!m_filterList.isEmpty())
        m_filterList.back()->setEnableOperatorCBox(true);

    connect(filt, SIGNAL(askToChangeNonEditablePart(const NonEditablePart*,QString)),
            this, SLOT(changeWhereText(const NonEditablePart*,QString)));
    connect(filt, SIGNAL(askToDeleteNonEditablePart(const NonEditablePart*)),
            this, SLOT(deleteNonEditablePartWhereText(const NonEditablePart*)));

    connect(delButton, SIGNAL(clicked()), m_deleteSignalMapper, SLOT(map()));
    m_deleteSignalMapper->setMapping(delButton, filt);

    m_filterList.push_back(filt);

    tableCBox->setCurrentIndex(0);
    filt->changeTable(0);

    filt->setField(fieldName);
    filt->setInputValue(value);
    filt->setEnableOperatorCBox(false);

    this->verifyEditabilityOfJoin();
}

void SearchWidget::deleteJoin(QObject* join)
{
    int founded = -1;
    for(int i = 0 ; i < m_joinList.size() && founded==-1 ; ++i)
    {
        if(m_joinList[i] == join)
            founded = i;
    }
    if(founded != -1)
    {
        delete m_joinList.takeAt(founded);
        ui->joinsFormLayout->removeRow(founded);
        if(founded == m_joinList.size() && !m_joinList.isEmpty())
        {
            m_joinList.back()->enableEditable(true);
            this->verifyEditabilityOfJoin();
        }

        ui->addJoinButton->setEnabled(true);
        this->updateAllTableList();
    }
}

void SearchWidget::deleteFilter(QObject* filter)
{
    int founded = -1;
    for(int i = 0 ; i < m_filterList.size() && founded==-1 ; ++i)
    {
        if(m_filterList[i] == filter)
            founded = i;
    }
    if(founded != -1)
    {
        delete m_filterList.takeAt(founded);
        ui->filtersFormLayout->removeRow(founded);
        if(founded == m_filterList.size() && !m_filterList.isEmpty())
            m_filterList.back()->setEnableOperatorCBox(false);

        if(m_joinList.size() > 0)
        {
            m_joinList.back()->enableEditable(true);
            this->verifyEditabilityOfJoin();
        }
    }
}

void SearchWidget::cleanJoinList()
{
    while(ui->joinsFormLayout->rowCount() > 1)
        ui->joinsFormLayout->removeRow(0);

    while(!m_joinList.isEmpty())
        delete m_joinList.takeLast();

    ui->joinTextEdit->clear();
    ui->addJoinButton->setEnabled(true);
}

void SearchWidget::cleanFilterList()
{
    while(ui->filtersFormLayout->rowCount() > 1)
        ui->filtersFormLayout->removeRow(0);

    while(!m_filterList.isEmpty())
        delete m_filterList.takeLast();

    ui->whereTextEdit->clear();
    ui->withTextEdit->clear();
}

void SearchWidget::deleteNonEditablePartJoinText(const NonEditablePart *part)
{
    ui->joinTextEdit->removeNonEditableText(part);
}

void SearchWidget::deleteNonEditablePartWhereText(const NonEditablePart *part)
{
    ui->whereTextEdit->removeNonEditableText(part);
}

void SearchWidget::changeJoinText(const NonEditablePart *part, const QString &joinTableName)
{
    QPair<QString, QString> p = this->searchJoinRelation(joinTableName);

    if(!p.first.isEmpty())
    {
        QString joinQuery;

        joinQuery = " INNER JOIN "+joinTableName+
                    " ON "+p.first+"="+p.second+" ";

        ui->joinTextEdit->changeNonEditableText(part, joinQuery);
    }
}

void SearchWidget::changeWhereText(const NonEditablePart *part, const QString &text)
{
    if(!m_joinList.isEmpty())
    {
        m_joinList.back()->enableEditable(true);
        this->verifyEditabilityOfJoin();
    }

    ui->whereTextEdit->changeNonEditableText(part, text);
}


void SearchWidget::tableChanged(int)
{
    this->cleanFilterList();
    this->cleanJoinList();
}

void SearchWidget::copyQueryToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(this->generateSqlQuery());
}

void SearchWidget::askToSearch()
{
    QuickSqlQuery quickquery(this->getCurTableName(),
                             ui->whereTextEdit->toPlainText(),
                             ui->withTextEdit->toPlainText(),
                             ui->joinTextEdit->toPlainText());
    emit askToSearch(quickquery);
}


void SearchWidget::verifyEditabilityOfJoin()
{
    if(!m_joinList.isEmpty())
    {
        QString joinTableName = m_joinList.back()->joinTableName();

        for(int i = 0 ; i < m_filterList.size() ; ++i)
        {
            if(m_filterList[i]->getTableName() == joinTableName)
                m_joinList.back()->enableEditable(false);
        }
    }
}


QString SearchWidget::generateSqlQuery()
{
    QuickSqlQuery quickquery(this->getCurTableName(),
                             ui->whereTextEdit->toPlainText(),
                             ui->withTextEdit->toPlainText(),
                             ui->joinTextEdit->toPlainText());

    return quickquery.generateSelectQuery(/*m_db*/).lastQuery();
}

const QList<QString> &SearchWidget::getTableList()
{
    m_tableList.clear();
    m_tableList.push_back(this->getCurTableName());
    for(int j = 0 ; j < m_joinList.size() ; ++j)
        m_tableList.push_back(m_joinList[j]->joinTableName());
    return m_tableList;
}

void SearchWidget::updateAllTableList()
{
    const QList<QString>& tableList = this->getTableList();
    for(int i = 0 ; i < m_filterList.size() ; ++i)
        m_filterList[i]->updateTableBox(tableList);
}


void SearchWidget::on_helpButton_clicked()
{
    QMessageBox::about(this,tr("Help"),tr("Use Quick Filter to add simple conditions like specify the name of a Museum."
                                          "For text-like filters, you can use '%' to represent any information. E.g. '%pou' will "
                                          "research for all results which end with 'pou'. \n"
                                          "Likewise, '_' represent any non-empty character. E.g. 'a__' will research"
                                          "for all results in 3 characters that start with 'a'. \n\n"
                                          "Use Quick Join, combined with Quick Filters, to add conditions on parents or childs.\n"
                                          "E.g. in table Material, to search for all 'Skull' in the museum 'IRNSB' :\n"
                                          "-Select Material table\n"
                                          "-Add Quick Join to Individual\n"
                                          "-Add Quick Filter, set it to 'Individual' and 'MuseumID' with value 'IRSNB'\n"
                                          "-Add Quick Filter Material.MaterialTypeID with value 'Skull'\n"
                                          "Or alternatively, you can replace the last operation by the following two:\n"
                                          "-Add Quick Join to MaterialType\n"
                                          "-Add Quick Filter MaterialType.Name with value 'Skull'.\n"
                                          "To search individual by inventory number:\n"
                                          "-Choose Individual table\n"
                                          "-Add Quick Join to Material\n"
                                          "-Add Quick Filter Material.InventoryNumber and choose the desired value."));
}
