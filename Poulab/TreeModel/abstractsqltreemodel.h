#ifndef ABSTRACTSQLTREEMODEL_H
#define ABSTRACTSQLTREEMODEL_H

#include <QAbstractItemModel>
#include <QMultiMap>
#include "SqlDatum/sqldatum.h"

class AbstractSqlTreeModel : public QAbstractItemModel
{
public:
    AbstractSqlTreeModel(QList<SqlDatum> *data = nullptr, AbstractSqlTable *parentTable = nullptr);

    void initializeData();

    QModelIndex findData(const QVariant &toFind, const QModelIndex &parent = QModelIndex());

    virtual QVariant getDataFromSqlDatum(const SqlDatum *datum, int role) const = 0 ;

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int getChildCount(int ID = -1) const;
    int getRow(SqlDatum *datum, int parentID = -1) const;
    SqlDatum *getParent(SqlDatum *datum) const;
    SqlDatum *getChild(int row, int parentID = -1) const;

    void enableNoChoice(bool b = true);

    void reset();

protected:

    bool m_noChoiceEnabled;
    SqlDatum *m_noChoiceDatum;

    QList<SqlDatum> *m_dataPointer;

    QMap<int, SqlDatum*> m_data;
    QMultiMap<int, SqlDatum*> m_childMap;

    QString m_parentingField;
};

#endif // ABSTRACTSQLTREEMODEL_H
