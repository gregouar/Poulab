/** This widget allows the user to quickly construct complex SQL query for searching in the database.
 * The user can choose a table to search in it, and then add filters.
 * He also has the possibility to make quick join with related table in order to do more complex filtering.
**/

#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QComboBox>
#include "dbmanager.h"
#include "CustomWidgets/partiallyeditabletextbox.h"

#include "SearchWidget/filterform.h"
#include "SearchWidget/joinform.h"


namespace Ui {
class SearchWidget;
}



class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(DbManager *db, QWidget *parent = nullptr);
    ~SearchWidget();

    void setCurTable(const QString &tablename);
    QString getCurTableName();

    QPair<QString, QString> searchJoinRelation(QString joinTable);

signals:
    void askToSearch(const QuickSqlQuery &);

public slots:
    void addFilter(const QString &fieldName = "", QVariant value = QVariant());
    void addJoin(const QString &childTableName = "");

    void changeWhereText(const NonEditablePart *part, const QString &text);
    void deleteNonEditablePartWhereText(const NonEditablePart *part);
    void deleteFilter(QObject* filter);

    void changeJoinText(const NonEditablePart *part, const QString &text);
    void deleteNonEditablePartJoinText(const NonEditablePart *part);
    void deleteJoin(QObject* join);

private slots:
    void tableChanged(int);
    void copyQueryToClipboard();
    void askToSearch();

    void on_helpButton_clicked();

    void updateAllTableList();

protected:
    void verifyEditabilityOfJoin();
    void cleanJoinList();
    void cleanFilterList();
    QString generateSqlQuery();
    const QList<QString> &getTableList();

private:
    Ui::SearchWidget *ui;

    DbManager *m_db;

    QList<FilterForm*> m_filterList;
    QList<JoinForm*> m_joinList;
    QSignalMapper* m_deleteSignalMapper;

    QList<QString> m_tableList;
};

#endif // SEARCHWIDGET_H
