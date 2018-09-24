#include "statisticswidget.h"
#include "ui_statisticswidget.h"

StatisticsWidget::StatisticsWidget(QWidget *parent) : QWidget(parent),
  ui(new Ui::StatisticsWidget)
{
    ui->setupUi(this);
}

StatisticsWidget::~StatisticsWidget()
{
    delete ui;
}

void StatisticsWidget::updateStatistics(DbManager *dbManager)
{
    ui->museumNbr->setText(QVariant(dbManager->count("Museum")).toString());
    ui->speciesNbr->setText(QVariant(dbManager->count("Species")).toString());
    ui->individualNbr->setText(QVariant(dbManager->count("Individual")).toString());
    ui->materialNbr->setText(QVariant(dbManager->count("Material")).toString());
    ui->measurementNbr->setText(QVariant(dbManager->count("Measurement")).toString());
}
