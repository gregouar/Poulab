/** This is the default widget use to show search results (and full tables). **/

#ifndef SHOWLISTWIDGET_H
#define SHOWLISTWIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QItemSelection>
#include <QSortFilterProxyModel>

#include "SqlDatum/sqldatum.h"

namespace Ui {
class ShowListWidget;
}

class ShowListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowListWidget(QWidget *parent = nullptr);
    virtual ~ShowListWidget();

    virtual void setTableModel(QAbstractItemModel *model, bool explorable = false);
    void setTitle(const QString &);

signals:
    void askToAddItem();
    void askToEditItem(int);
    void askToExploreItem(int);
    void askToSearchInside();

public slots:

protected slots:
    virtual void handleTableViewClick(const QModelIndex& index);
    void handleTableViewDoubleClick(const QModelIndex& index);
    virtual void openButtonClicked();
    void editButtonClicked();

protected:
    Ui::ShowListWidget *ui;
    int m_selectedID;
    bool m_explorable;

    QSortFilterProxyModel *m_sortingProxy;

};

#endif // SHOWLISTWIDGET_H
