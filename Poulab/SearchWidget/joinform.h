/** This not very well designed class represent a row in the form of all joins for the SearchWidget.
 * A join is a basic INNER JOIN sql query part that is automatically constructed from inputs chosed by the user.
 **/

#ifndef JOINFORM_H
#define JOINFORM_H

#include <QObject>

#include <QComboBox>
#include <QPushButton>
#include "CustomWidgets/partiallyeditabletextbox.h"
#include "SqlTable/abstractsqltable.h"

class JoinForm : public QObject
{
    Q_OBJECT

public:
    JoinForm(QComboBox *joinCBox,
             QPushButton *delButton,
             const NonEditablePart *nonEditablePart,
             const DbManager *db);
    ~JoinForm();

    QString joinTableName();

public slots:
    void changeJoinTable(int);

    void enableEditable(bool = true);

signals:
    void askToChangeNonEditablePart(const NonEditablePart*,QString);
    void askToDeleteNonEditablePart(const NonEditablePart*);

private:
    QComboBox *m_joinCBox;
    QPushButton *m_delButton;
    const NonEditablePart *m_nonEditablePart;
    const DbManager *m_db;

};

#endif // JOINFORM_H
