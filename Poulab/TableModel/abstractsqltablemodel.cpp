#include "abstractsqltablemodel.h"

AbstractSqlTableModel::AbstractSqlTableModel(QList<SqlDatum> *data)
{
    m_data = data;
}


int AbstractSqlTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(m_data != nullptr)
        return m_data->size();
    return 0;
}

QVariant AbstractSqlTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_data->size() || index.row() < 0)
        return QVariant();

    const SqlDatum *datum = &m_data->at(index.row());

    if(datum == nullptr)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return datum->getID();
        else
            return this->getStoredValue(datum, index.column());
    } else if(role == Qt::UserRole)
        return datum->getID();

    return QVariant();
}


QVariant AbstractSqlTableModel::getStoredValue(const SqlDatum* datum, int column) const
{
    return m_storedValues[datum][column];
}

void AbstractSqlTableModel::generateStoredValues(const QModelIndex &index)
{
    if(m_data != nullptr)
    for(int i = 0 ; i < this->rowCount(index) ; ++i)
    {
        const SqlDatum *datum = &m_data->at(i);
        for(int j = 1 ; j < this->columnCount(index) ; ++j)
        {
            m_storedValues[datum][j] = this->generateStoredValue(datum,j);
        }
    }
}

void AbstractSqlTableModel::reset()
{
    this->beginResetModel();
    m_storedValues.clear();
    this->generateStoredValues();
    this->endResetModel();
}

