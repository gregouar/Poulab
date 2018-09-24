/** Each AbstractSqlTable should have a corresponding inherited AbstractSqlListModel.
 * It says how to fill a Combobox. It also gives the common name of a record on the table.
 * You only need to implement  getDataFromSqlDatum which should return the common name of the given datum.
**/

#ifndef ABSTRACTSQLLISTMODEL_H
#define ABSTRACTSQLLISTMODEL_H

#include <QAbstractListModel>

#include "SqlDatum/sqldatum.h"


class AbstractSqlListModel : public QAbstractListModel
{
public:
    AbstractSqlListModel(QList<SqlDatum> *data = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual QVariant getDataFromSqlDatum(const SqlDatum *datum, int role = Qt::DisplayRole) const = 0 ;

    void enableNoChoice(bool b = true);

    void reset();

protected:
    QList<SqlDatum> *m_data;
    bool m_noChoiceEnabled;
};

#endif // ABSTRACTSQLLISTMODEL_H
