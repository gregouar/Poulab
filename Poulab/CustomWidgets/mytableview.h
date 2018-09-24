/** This custom version of QTableView allows to resize automatically
 * the size of the column, depending on Qt::SizeHint (in %) of the header data.
**/

#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>

class MyTableView : public QTableView
{
    Q_OBJECT

public:
    MyTableView(QWidget * parent = 0);
    ~MyTableView();

    virtual void setModel(QAbstractItemModel * model);

public slots:
    void resizeTable();

protected:
    virtual void resizeEvent(QResizeEvent *event);

};

#endif // MYTABLEVIEW_H
