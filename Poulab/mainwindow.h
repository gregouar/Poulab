#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "AddItemWidget/abstractadditemwidget.h"
#include "AddItemWidget/addallmeasurementswidget.h"
#include "ShowListWidget/showlistwidget.h"
#include "ShowListWidget/showmeasurementwidget.h"
#include "ShowListWidget/showmeasurementtypewidget.h"
#include "ShowListWidget/showmaterialtypetreewidget.h"
#include "mainmenuwidget.h"
#include "statisticswidget.h"
#include "SearchWidget/searchwidget.h"

#include "CustomWidgets/lineeditdialog.h"

#include "dbmanager.h"

#include <QStack>

namespace Ui {
class MainWindow;
}

enum WIDGET_NAME
{
    WIDGET_MAINMENU,
    WIDGET_SHOWLIST,
    WIDGET_ADDITEM,
    WIDGET_STATISTICS,
    WIDGET_SEARCH,
    EXPLORE_ITEM,
    WIDGET_MATERIALTYPETREE,
};

struct HistoryAction
{
    WIDGET_NAME name;
    QString text;
    int value;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addToHistory(WIDGET_NAME name, const QString &text = "", int value = -1);

public slots:
    void showMainMenu();
    void showSearchList(const QString &tableName = QString(), int ID = -1);
    void showSearchList(const QuickSqlQuery &quickquery);
    void showMaterialTypeTree();
    void showAddItem(const int ID = -1);
    void showAddItem(const QString &tableName, const int ID = -1);
    void showAddAllMeasurements();
    void showStatisticsWidget();
    void showSearchWidget();
    void searchInsideCurTable();
    void showBack();

    void hideEverything();
    void disableEverything();

    void connectedToDb(bool);
    void restart();

private slots:
    void exploreItem(int ID);
    void executeQuery();

protected:
    void addAddItemWidget(const QString tableName, AbstractAddItemWidget* widget);

private:
    Ui::MainWindow *ui;

    MainMenuWidget *m_mainMenu;
    StatisticsWidget *m_statisticsWidget;
    SearchWidget *m_searchWidget;

    ShowListWidget *m_showListWidget;
    ShowMeasurementWidget *m_showMeasurementWidget;
    ShowMeasurementTypeWidget *m_showMeasurementTypeWidget;
    ShowMaterialTypeTreeWidget *m_showMaterialTypeTreeWidget;

    QMap<QString, AbstractAddItemWidget*> m_addItemWidgetList;
    AddAllMeasurementsWidget* m_addAllMeasurementsWidget;
    QSignalMapper* m_actionAddItemMapper;

    LineEditDialog *m_execQueryDialog;

    QStack<HistoryAction> m_historyStack;

    QString m_curTableName;
    QString m_curParentTableName;
    int m_curParentID;

    DbManager m_dbManager;
};

#endif // MAINWINDOW_H
