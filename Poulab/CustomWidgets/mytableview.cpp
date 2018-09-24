#include "mytableview.h"

#include <QDebug>
#include <QHeaderView>

MyTableView::MyTableView(QWidget * parent) : QTableView(parent)
{

}

MyTableView::~MyTableView()
{

}


void MyTableView::setModel(QAbstractItemModel * model)
{
    QTableView::setModel(model);
    this->resizeTable();
}


void MyTableView::resizeTable()
{
    if(this->model() != nullptr)
    {
        int n = this->model()->columnCount();
        int totalWidth = 0;

        for(int i = 0 ; i < n-1 ; ++i)
        {
            double width = 0;
            width = (this->model()->headerData(i,Qt::Horizontal,Qt::SizeHintRole).toDouble());

            if(width == 0)
                width = 1/(double)n;

            width *= (double)geometry().width();
            QTableView::setColumnWidth(i, (int)width);
            totalWidth += (int)width;
        }

        QTableView::horizontalHeader()->setSectionResizeMode(
                n-1, QHeaderView::Stretch);
    }
}


void MyTableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    this->resizeTable();
}


