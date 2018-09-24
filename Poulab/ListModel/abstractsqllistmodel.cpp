#include "abstractsqllistmodel.h"

AbstractSqlListModel::AbstractSqlListModel(QList<SqlDatum> *data)
{
    m_data = data;
    m_noChoiceEnabled = false;
}


int AbstractSqlListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(m_data != nullptr)
        return m_data->size() + m_noChoiceEnabled;
    return m_noChoiceEnabled;
}


QVariant AbstractSqlListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row()-m_noChoiceEnabled >= m_data->size() || index.row() < 0)
        return QVariant();

    if(index.column() != 0)
        return QVariant();

    if(m_noChoiceEnabled && index.row() == 0)
    {
        if(role == Qt::DisplayRole)
            return QVariant("--None--");
        else if(role == Qt::UserRole)
            return -1;
    }

    const SqlDatum *datum = &m_data->at(index.row()-m_noChoiceEnabled);

    if(datum == nullptr)
        return QVariant();

    return this->getDataFromSqlDatum(datum, role);
}


void AbstractSqlListModel::enableNoChoice(bool b)
{
    m_noChoiceEnabled = b;
}

void AbstractSqlListModel::reset()
{
    this->beginResetModel();
    this->endResetModel();
}

