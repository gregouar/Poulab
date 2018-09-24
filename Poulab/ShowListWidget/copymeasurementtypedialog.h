#ifndef COPYMEASUREMENTTYPEDIALOG_H
#define COPYMEASUREMENTTYPEDIALOG_H

#include <QDialog>
#include <QAbstractItemModel>

#include "CustomWidgets/treebox.h"

class CopyMeasurementTypeDialog : public QDialog
{
    Q_OBJECT
public:
    CopyMeasurementTypeDialog(QAbstractItemModel *boxmodel);
    QVariant chosenData(int role = Qt::DisplayRole);

private:
    TreeBox *m_cbox;
};

#endif // COPYMEASUREMENTTYPEDIALOG_H
