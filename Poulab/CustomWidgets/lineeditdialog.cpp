#include "lineeditdialog.h"
#include <QLayout>
#include <QPushButton>
#include <QLabel>

LineEditDialog::LineEditDialog(const QString &title, const QString &text, const QString &value) :
    QDialog(nullptr, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    QGridLayout* layout =  new QGridLayout();
    setLayout(layout);

    this->setWindowTitle(title);
    this->resize(250,150);

    layout->addWidget(new QLabel(text,this),0,0,1,2);

    m_lineEdit = new QLineEdit(value, this);
    layout->addWidget(m_lineEdit,1,0,1,2);

    layout->setRowMinimumHeight(2, 50);

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
       cleanValue();
       reject();
    });
}


QString LineEditDialog::value()
{
    return m_lineEdit->text();
}

void LineEditDialog::setValue(const QString &value)
{
    m_lineEdit->setText(value);
}


void LineEditDialog::cleanValue()
{
    this->setValue("");
}


