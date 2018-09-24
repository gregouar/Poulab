#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>

#include "dbmanager.h"

namespace Ui {
class StatisticsWidget;
}

class StatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    ~StatisticsWidget();

signals:

public slots:
    void updateStatistics(DbManager *db);

private:
    Ui::StatisticsWidget *ui;
};

#endif // STATISTICSWIDGET_H
