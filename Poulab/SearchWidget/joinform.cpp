#include "joinform.h"

#include <QDebug>

#include "dbmanager.h"

JoinForm::JoinForm(QComboBox *joinCBox,
                   QPushButton *delButton,
                   const NonEditablePart *nonEditablePart,
                   const DbManager *dbManager)
{
    m_joinCBox = joinCBox;
    m_delButton = delButton;

    m_nonEditablePart = nonEditablePart;
    m_db = dbManager;

    connect(m_joinCBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeJoinTable(int)));
}

JoinForm::~JoinForm()
{
    askToDeleteNonEditablePart(m_nonEditablePart);
}

void JoinForm::enableEditable(bool b)
{
    m_delButton->setEnabled(b);
    m_joinCBox->setEnabled(b);
}

QString JoinForm::joinTableName()
{
    return m_joinCBox->currentText();
}

void JoinForm::changeJoinTable(int)
{
    emit askToChangeNonEditablePart(m_nonEditablePart, this->joinTableName());
}

