#include "copymeasurementtypedialog.h"

#include <QLayout>
#include <QPushButton>
#include <QLabel>

CopyMeasurementTypeDialog::CopyMeasurementTypeDialog(QAbstractItemModel *boxmodel) :
    QDialog(nullptr, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    QGridLayout* layout =  new QGridLayout();
    setLayout(layout);

    this->setWindowTitle("Copy measurement types");
    this->resize(250,150);

    layout->addWidget(new QLabel("Please choose material type target:",this),0,0,1,2);

    m_cbox = new TreeBox(this);
    m_cbox->setModel(boxmodel);
    layout->addWidget(m_cbox,1,0,1,2);

    layout->setRowStretch(2,1);

    QPushButton* ok = new QPushButton("Ok",this);
    layout->addWidget(ok,3,1,1,1);
    connect(ok, &QPushButton::clicked, this, [this]()
    {
       accept();
    });


    QPushButton* cancelButton = new QPushButton("Cancel",this);
    layout->addWidget(cancelButton,3,0,1,1);
    connect(cancelButton, &QPushButton::clicked, this, [this]()
    {
       reject();
    });
}


QVariant CopyMeasurementTypeDialog::chosenData(int role)
{
    return m_cbox->currentData(role);
}

