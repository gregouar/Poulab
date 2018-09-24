/** This class manage the filling of a table correspoding to the list of data it is given.
 * You need to implement one per table in the database and you need to implement columnCount(..),
 * which say the number of columns you want to show, headerData(..) for the title of the columns,
 * and generateStoredValue(..) for filling the cells.
**/

#ifndef ABSTRACTSQLTABLEMODEL_H
#define ABSTRACTSQLTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "SqlDatum/sqldatum.h"

class AbstractSqlTableModel : public QAbstractTableModel
{
public:
    AbstractSqlTableModel(QList<SqlDatum> *data = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    QVariant getStoredValue(const SqlDatum*, int column) const;

    virtual int columnCount(const QModelIndex &parent) const = 0;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const = 0;

    void reset();

protected:
    virtual QVariant generateStoredValue(const SqlDatum*, int column) const = 0;
    virtual void generateStoredValues(const QModelIndex &index = QModelIndex());

protected:
    QList<SqlDatum> *m_data;
    QMap<const SqlDatum *,QMap<int,QVariant>> m_storedValues;
    QString m_lastQuery;

};

#endif // ABSTRACTSQLTABLEMODEL_H
