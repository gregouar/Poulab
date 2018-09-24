#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

#include <QDebug>

#include "SqlTable/museumsqltable.h"
#include "SqlTable/speciessqltable.h"
#include "SqlTable/individualsqltable.h"
#include "SqlTable/materialtypesqltable.h"
#include "SqlTable/materialsqltable.h"
#include "SqlTable/measurementtypesqltable.h"
#include "SqlTable/measurementsqltable.h"

DbManager::DbManager(QObject *parent) : QObject(parent)
{
    m_tablesList.insert("Museum",new MuseumSqlTable(this));
    m_tablesList.insert("Species",new SpeciesSqlTable(this));

    m_tablesList.insert("Individual",new IndividualSqlTable(this));
    m_tablesList.insert("Material",new MaterialSqlTable(this));
    m_tablesList.insert("Measurement",new MeasurementSqlTable(this));

    m_tablesList.insert("MaterialType",new MaterialTypeSqlTable(this));
    m_tablesList.insert("MeasurementType",new MeasurementTypeSqlTable(this));
}

DbManager::~DbManager()
{
    while(!m_tablesList.isEmpty())
    {
        delete m_tablesList.first();
        m_tablesList.erase(m_tablesList.begin());
    }
}


const AbstractSqlTable* DbManager::getTable(const QString &tableName) const
{
    QMap<QString, AbstractSqlTable*>::const_iterator  i = m_tablesList.find(tableName);
    if(i != m_tablesList.end())
        return i.value();
    else
    {/*deal with error*/}

    return nullptr;
}

QList<QString> DbManager::getTableNameList() const
{
    return m_tablesList.keys();
}


const QList<AbstractSqlTable*> DbManager::getTableList() const
{
    return m_tablesList.values();
}

AbstractSqlTable* DbManager::getNonConstTable(const QString &tableName)
{
    QMap<QString, AbstractSqlTable*>::iterator  i = m_tablesList.find(tableName);
    if(i != m_tablesList.end())
        return i.value();
    else
    {/*deal with error*/}

    return nullptr;
}


QAbstractTableModel* DbManager::getTableModel(const QuickSqlQuery &quickquery)
{
    AbstractSqlTable* t = this->getNonConstTable(quickquery.tableName());
    if(t != nullptr)
    {
        t->readTable(quickquery);
        return t->getTableModel();
    }
    else
    {/*deal with error*/}
    return nullptr;
}


AbstractSqlListModel *DbManager::getListModel(const QuickSqlQuery &quickquery)
{
    AbstractSqlTable* t = this->getNonConstTable(quickquery.tableName());
    if(t != nullptr)
    {
        t->readTable(quickquery);
        return t->getListModel();
    }
    else
    {/*deal with error*/}
    return nullptr;
}

int DbManager::count(const QString &tableName) const
{
    return this->count(QuickSqlQuery(tableName));
}

int DbManager::count(const QuickSqlQuery &quickquery) const
{
    QSqlQuery query = quickquery.generateCountQuery(/*this*/);
    query.next();
    return query.value(0).toInt();
}


AbstractSqlTreeModel *DbManager::getTreeModel(const QuickSqlQuery &quickquery)
{
    AbstractSqlTable* t = this->getNonConstTable(quickquery.tableName());
    if(t != nullptr)
    {
        t->readTable(quickquery);
        return t->getTreeModel();
    }
    else
    {/*deal with error*/}
    return nullptr;
}

SqlDatum DbManager::getFirstMatchDatum(const QString &tableName, const QString &filter) const
{
    return getFirstMatchDatum(QuickSqlQuery (tableName,filter));
}

SqlDatum DbManager::getFirstMatchDatum(const QuickSqlQuery &quickquery) const
{
    const AbstractSqlTable* t = this->getTable(quickquery.tableName());
    if(t != nullptr)
        return t->getFirstMatchDatum(quickquery);
    return SqlDatum();
}

SqlDatum DbManager::getDatumFromId(const QString &tableName, const int ID) const
{
    if(ID == -1)
        return nullptr;

    const AbstractSqlTable* t = this->getTable(tableName);
    if(t != nullptr)
        return t->getDatumFromID(ID);
    return SqlDatum();
}

QString DbManager::searchParentLinkFieldName(const QString &curTableName, const QString &parentTableName)  const
{
    const AbstractSqlTable* t = this->getTable(curTableName);
    return t->getParentFieldName(parentTableName);
}


QString DbManager::getItemListName(const QString &tableName, int ID)
{
    AbstractSqlTable* t = this->getNonConstTable(tableName);
    if(t != nullptr)
    {
        SqlDatum d = t->getDatumFromID(ID);
        if(d.isValid() && d.getID() != -1)
        {
            if(t->getListModel() == nullptr)
                t->readTable();
            return t->getListModel()->getDataFromSqlDatum(&d).toString();
        }
        else
        {
            return "Missing element";
        }
    }
    else
    {/*deal with error*/}

    return QString();

}

const QString &DbManager::getFilePath()
{
    return m_dbFilePath;
}

QDir DbManager::getDirectory()
{
    QDir dir(this->getFilePath());
    dir.cdUp();
    return dir;
}


void DbManager::createDb()
{
    QString db_name = QFileDialog::getSaveFileName(nullptr, tr("New database"),
                               "./",
                               tr("SQLite Database (*.sqlite)"));

    if( !db_name.isEmpty())
        this->createDb(db_name);
}

void DbManager::createDb(const QString &db_name)
{
    QFile file(db_name);
    if(file.exists() == true
    && file.remove() == false)
    {
        QMessageBox::critical(nullptr, QObject::tr("Cannot create database"),
            QObject::tr("Unable to remove old database.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        connectToDb(db_name);

        this->createAllNewTables();
    }
}

void DbManager::openDb()
{
    QString db_name = QFileDialog::getOpenFileName(nullptr, tr("Open database"),
                               "./",
                               tr("SQLite Database (*.sqlite)"));

    if( !db_name.isEmpty())
        this->connectToDb(db_name);
}

void DbManager::saveDbAs()
{
    QString db_name = QFileDialog::getSaveFileName(nullptr, tr("Save database as"),
                               m_dbFilePath,
                               tr("SQLite Database (*.sqlite)"));
    if(!db_name.isEmpty())
    {
        QFile file(db_name);
        if(file.exists() == true
        && file.remove() == false)
        {
            QMessageBox::critical(nullptr, QObject::tr("Cannot save database as"),
                QObject::tr("Unable to erase old database file.\n\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
        } else {
            QFile::copy(m_dbFilePath,db_name);
            this->connectToDb(db_name);
        }
    }
}

void DbManager::closeDb()
{
    m_db.close();
    emit connected(false);
}

void DbManager::connectToDb(const QString &db_name)
{
    bool ok = true;

    this->closeDb();
    if(m_db.connectionName().isEmpty())
        m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(db_name);
    if(!m_db.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        ok = false;
    }

    m_dbFilePath = db_name;
    this->verifyDatabaseIntegrity();

    emit connected(ok);
}


void DbManager::createAllNewTables()
{
    QMap<QString,AbstractSqlTable*>::iterator i;
    for(i = m_tablesList.begin() ; i != m_tablesList.end() ; ++i)
        i.value()->createNewTable();
}

void DbManager::verifyDatabaseIntegrity()
{
    QMap<QString,AbstractSqlTable*>::iterator i;
    for(i = m_tablesList.begin() ; i != m_tablesList.end() ; ++i)
        i.value()->verifyTableIntegrity();
}

void DbManager::readTable(const QuickSqlQuery &quickquery)
{
    QMap<QString, AbstractSqlTable*>::iterator  i = m_tablesList.find(quickquery.tableName());
    if(i != m_tablesList.end())
    {
        if(i.value() != nullptr)
            i.value()->readTable(quickquery);
    }
    else
    {/*deal with error*/}
}


bool DbManager::executeQuery(const QString &text)
{
    QSqlQuery query(text);
    bool r = query.exec();
    this->verifyDatabaseIntegrity();
    return r;
}



