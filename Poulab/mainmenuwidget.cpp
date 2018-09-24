#include "mainmenuwidget.h"
#include "ui_mainmenuwidget.h"

#include <QDir>
#include <QDebug>
#include <QSignalMapper>

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent),
  ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(QString)), this, SIGNAL(askToShowList(QString)));

    connect(ui->museumButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->speciesButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->individualButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->materialButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->measurementButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->measurementTypeButton, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper->setMapping(ui->museumButton, "Museum");
    signalMapper->setMapping(ui->speciesButton, "Species");
    signalMapper->setMapping(ui->individualButton, "Individual");
    signalMapper->setMapping(ui->measurementButton, "Measurement");
    signalMapper->setMapping(ui->materialButton, "Material");
    signalMapper->setMapping(ui->measurementTypeButton, "MeasurementType");

    connect(ui->materialTypeButton, SIGNAL (clicked()), this, SIGNAL (askToShowMaterialTypeTree()));

    connect(ui->searchButton, SIGNAL (clicked()), this, SIGNAL (askToShowSearchWidget()));
    connect(ui->statisticsButton, SIGNAL (clicked()), this, SIGNAL (askToShowStatisticsWidget()));
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
}
