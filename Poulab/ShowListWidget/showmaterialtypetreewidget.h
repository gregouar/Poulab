#ifndef SHOWMATERIALTYPETREEWIDGET_H
#define SHOWMATERIALTYPETREEWIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QItemSelection>

#include "SqlDatum/sqldatum.h"
#include "TreeModel/abstractsqltreemodel.h"

namespace Ui {
class ShowMaterialTypeTreeWidget;
}


class ShowMaterialTypeTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowMaterialTypeTreeWidget(QWidget *parent = nullptr);
    virtual ~ShowMaterialTypeTreeWidget();

    virtual void setTreeModel(AbstractSqlTreeModel *model);
    void setTitle(const QString &);

signals:
    void askToAddItem();
    void askToEditItem(int);
    void askToExploreItem(int);
    void askToSearchInside();

public slots:

protected slots:
    void handleTableViewClick();
    void handleTableViewDoubleClick(const QModelIndex& index);
    void openButtonClicked();
    void editButtonClicked();

protected:
    Ui::ShowMaterialTypeTreeWidget *ui;
    int m_selectedID;
    bool m_explorable;
};

#endif // SHOWMATERIALTYPETREEWIDGET_H

