/** This custom dialog allows to ask the user to input a line of text. **/

#ifndef LINEEDITDIALOG_H
#define LINEEDITDIALOG_H

#include <QDialog>
#include <QLineEdit>

class LineEditDialog : public QDialog
{
public:
    LineEditDialog(const QString &title = "",
                   const QString &text = "",
                   const QString &value = "");

    QString value();

    void setValue(const QString &value);

protected slots:
    void cleanValue();

private:
    QLineEdit *m_lineEdit;
};

#endif // LINEEDITDIALOG_H
