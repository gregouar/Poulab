#include "abstractsqltreemodel.h"

#include <QDebug>

AbstractSqlTreeModel::AbstractSqlTreeModel(QList<SqlDatum> *data, AbstractSqlTable *parentTable)
{
    m_dataPointer = data;
    m_noChoiceDatum = new SqlDatum(parentTable);
}

void AbstractSqlTreeModel::initializeData()
{
    m_data.clear();
    m_childMap.clear();

    QList<SqlDatum>::iterator i;

    for(i = m_dataPointer->begin() ; i != m_dataPointer->end() ; ++i)
    {
        m_data.insert(i->getID(), &(*i));
        m_childMap.insert(i->getFieldValue(m_parentingField).toInt(), &(*i));
    }

    const AbstractSqlTable *t = m_noChoiceDatum->getParentTable();

    delete m_noChoiceDatum;
    m_noChoiceDatum = new SqlDatum(t);
    m_noChoiceDatum->setFieldValue("Name", QVariant("--None--"));
    m_noChoiceDatum->setFieldValue(m_parentingField, QVariant(-1));
}


QModelIndex AbstractSqlTreeModel::findData(const QVariant & toFind, const QModelIndex &parent)
{
    int n = this->rowCount(parent);

    for(int i = 0 ; i < n ; ++i)
    {
        QModelIndex curIndex = this->index(i,0,parent);
        if(this->data(curIndex, Qt::UserRole) == toFind)
            return curIndex;
        else
        {
            QModelIndex f = findData(toFind, curIndex);
            if(f.isValid())
                return f;
        }
    }

    return QModelIndex();
}

void AbstractSqlTreeModel::enableNoChoice(bool b)
{
    m_noChoiceEnabled = b;
}

QVariant AbstractSqlTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const SqlDatum *datum =  static_cast<SqlDatum*>(index.internalPointer());

    return getDataFromSqlDatum(datum,role);

    return QVariant();
}

Qt::ItemFlags AbstractSqlTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QModelIndex AbstractSqlTreeModel::index(int row, int column,
                  const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    SqlDatum *parentDatum;

    if (!parent.isValid())
        parentDatum = nullptr;
    else
        parentDatum = static_cast<SqlDatum*>(parent.internalPointer());

    SqlDatum *child  = nullptr;

    if(parentDatum == nullptr)
        child = this->getChild(row);
    else
        child = this->getChild(row, parentDatum->getID());

    if(child != nullptr)
        return createIndex(row, column, child);

    return QModelIndex();
}

QModelIndex AbstractSqlTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    SqlDatum *childItem = static_cast<SqlDatum*>(index.internalPointer());

    SqlDatum *parentItem = this->getParent(childItem);

    if (parentItem == nullptr)
        return QModelIndex();

    return createIndex(this->getRow(parentItem, parentItem->getFieldValue(m_parentingField).toInt()), 0, parentItem);
}

int AbstractSqlTreeModel::rowCount(const QModelIndex &parent) const
{
    SqlDatum *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return this->getChildCount();
    else
        parentItem = static_cast<SqlDatum*>(parent.internalPointer());

    if(parentItem == m_noChoiceDatum)
        return 0;

    return this->getChildCount(parentItem->getID());
}

int AbstractSqlTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int AbstractSqlTreeModel::getChildCount(int ID) const
{
    bool addOne = false;

    if(ID == -1 && m_noChoiceEnabled)
        addOne = true;

    return m_childMap.count(ID) + addOne;
}

int AbstractSqlTreeModel::getRow(SqlDatum *datum, int parentID) const
{

    bool addOne = false;

    if(parentID == -1 && m_noChoiceEnabled)
        addOne = true;

    return m_childMap.values(parentID).indexOf(datum) + addOne ;
}

SqlDatum *AbstractSqlTreeModel::getParent(SqlDatum *datum) const
{
    if(datum == nullptr)
        return nullptr;

    int parentID = datum->getFieldValue(m_parentingField).toInt();

    if(parentID == -1)
        return nullptr;

    return m_data[parentID];
}

SqlDatum *AbstractSqlTreeModel::getChild(int row, int parentID) const
{
    bool addOne = false;

    if(parentID == -1 && m_noChoiceEnabled)
    {
        addOne = true;
        if(row == 0)
            return m_noChoiceDatum;
    }

    return m_childMap.values(parentID).at(row-addOne);
}


void AbstractSqlTreeModel::reset()
{
    this->beginResetModel();
    initializeData();
    this->endResetModel();
}



