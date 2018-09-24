#include "abstractadditemwidget.h"
#include "ui_additemwidget.h"
#include "SqlTable/abstractsqltable.h"
#include "dbmanager.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>

#include <QTreeView>

#include <QDebug>

AbstractAddItemWidget::AbstractAddItemWidget(const AbstractSqlTable *sqlTable, QWidget *parent) :
    QWidget(parent),
    mainui(new Ui::AddItemWidget)
{
    m_curDatum = nullptr;
    m_sqlTable = sqlTable;

    mainui->setupUi(this);

    connect(mainui->addItemButton, SIGNAL (clicked()), this, SLOT (addItem()));
    connect(mainui->deleteItemButton, SIGNAL (clicked()), this, SLOT (deleteItem()));
    connect(mainui->cancelButton, SIGNAL (clicked()), this, SIGNAL (cancel()));

    mainui->addItemButton->setShortcut(QKeySequence(Qt::Key_Enter));

    mainui->deleteItemButton->setText("Delete "+m_sqlTable->getTableName());
}

AbstractAddItemWidget::~AbstractAddItemWidget()
{
    delete mainui;
}

void AbstractAddItemWidget::setDatum(const SqlDatum &datum)
{
    m_curDatum = datum;

    this->generateInputFields();

    if(datum.isValid() && datum.getID() != -1)
    {
        QMap<QString, QObject*>::iterator i;

        mainui->deleteItemButton->setEnabled(true);
        mainui->addItemButton->setText("Edit "+m_sqlTable->getTableName());
        mainui->title->setText("Edit existing "+m_sqlTable->getTableName());

        for(i = m_inputsList.begin() ; i != m_inputsList.end() ; ++i)
        {
            const SqlField *f = m_sqlTable->getSqlField(i.key());
            if(f->type() == SQLFIELD_LINK) {
                QComboBox *cBox = (QComboBox*)i.value();

                if(f->treeView())
                {
                    AbstractSqlTreeModel *tree = (AbstractSqlTreeModel*)cBox->model();
                    QModelIndex founded = tree->findData(datum.getFieldValue(i.key()), QModelIndex());

                    QModelIndex oldRoot = cBox->rootModelIndex();
                    cBox->setRootModelIndex(cBox->model()->parent(founded));
                    cBox->setCurrentIndex(founded.row());
                    cBox->setRootModelIndex(oldRoot);
                } else
                    cBox->setCurrentIndex(cBox->findData(datum.getFieldValue(i.key())));

            } else if(f->type() == SQLFIELD_SPECIAL) {
                ((QComboBox*)i.value())->setCurrentIndex(datum.getFieldValue(i.key()).toInt());
            } else
                    ((QLineEdit*)i.value())->setText(datum.getFieldValue(i.key()).toString());
        }
    } else {
        mainui->deleteItemButton->setEnabled(false);
        mainui->addItemButton->setText("Add "+m_sqlTable->getTableName());
        mainui->title->setText("Create new "+m_sqlTable->getTableName());
    }

    mainui->addItemButton->setEnabled(true);

    emit datumSet(datum.getID());
}


void AbstractAddItemWidget::setParentDefaultChoice(const QString &parentField, int ID)
{
    if(!parentField.isEmpty() && ID != -1)
    {
        const SqlField *f = m_sqlTable->getSqlField(parentField);
        QComboBox *cBox = (QComboBox*)m_inputsList.find(parentField).value();

        if(f->treeView())
        {
            AbstractSqlTreeModel *tree = (AbstractSqlTreeModel*)cBox->model();
            QModelIndex founded = tree->findData(ID, QModelIndex());

            QModelIndex oldRoot = cBox->rootModelIndex();
            cBox->setRootModelIndex(cBox->model()->parent(founded));
            cBox->setCurrentIndex(founded.row());
            cBox->setRootModelIndex(oldRoot);
        } else
            cBox->setCurrentIndex(cBox->findData(ID));
    }
}


void AbstractAddItemWidget::addItem(const SqlDatum* datum)
{
    if(datum != nullptr)
    {
        mainui->addItemButton->setEnabled(false);
        datum->addToTable();
        emit AbstractAddItemWidget::itemAdded();
    } else {
        bool ok = true;

        SqlDatum d(m_sqlTable,this->getCurDatumID());

        QMap<QString, QObject*>::iterator i;
        for(i = m_inputsList.begin() ; i != m_inputsList.end() ; ++i)
        {
            const SqlField *f = m_sqlTable->getSqlField(i.key());
            if(f->type() == SQLFIELD_LINK) {
                QVariant data = ((QComboBox*)i.value())->currentData();
                if(data.isNull())
                {
                    if(f->notNull())
                    {
                        ok = false;

                        QMessageBox::critical(nullptr, QObject::tr("Cannot add item"),
                            "You must choose an item for "+i.key()+".", QMessageBox::Ok);
                    }

                    data = QVariant(-1);
                }

                if(data != -1)
                if(f->linkName() == m_sqlTable->getTableName())
                    if(m_sqlTable->getDatumFromID(data.toInt()).isChildOf(f, this->getCurDatumID()))
                    {
                        ok = false;
                        QMessageBox::critical(nullptr, QObject::tr("Cannot add item"),
                            QObject::tr("Cannot set item as subelement of itself."), QMessageBox::Ok);
                    }

                d.setFieldValue(i.key(), data);
            } else if(f->type() == SQLFIELD_SPECIAL)
            {
                d.setFieldValue(i.key(), ((QComboBox*)i.value())->currentIndex());
            } else
            {
                if(f->notNull() && ((QLineEdit*)i.value())->text().isEmpty())
                {
                    ok = false;

                    QMessageBox::critical(nullptr, QObject::tr("Cannot add item"),
                        "Field "+i.key()+" must not be empty.", QMessageBox::Ok);
                }
                d.setFieldValue(i.key(), ((QLineEdit*)i.value())->text());
            }
        }

        if(ok)
            this->addItem(&d);
    }
}

void AbstractAddItemWidget::deleteItem()
{
    if(m_curDatum.isValid() && m_curDatum.getID() != -1)
    {
         QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Delete item", "Are you sure you want to delete this item ?",
                                       QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::Yes) {
           m_curDatum.deleteFromTable();
           m_curDatum = SqlDatum();
           emit AbstractAddItemWidget::itemDeleted();
         }
    }
}

void AbstractAddItemWidget::generateInputFields()
{
    QMap<QString,QObject*>::iterator i;

    for(i = m_inputsList.begin() ; i != m_inputsList.end() ; ++i)
    {
        const SqlField *f = m_sqlTable->getSqlField(i.key());
        if(f->type() == SQLFIELD_LINK)
        {
            QComboBox *cBox = (QComboBox*)i.value();
            cBox->clear();

            if(f->treeView())
            {
                AbstractSqlTreeModel *im = m_sqlTable->getParentDb()->getTreeModel(f->linkName());
                if(im != nullptr)
                {
                    im->enableNoChoice(!f->notNull());
                    cBox->setModel(im);
                }
            } else {
                AbstractSqlListModel *lm = m_sqlTable->getParentDb()->getListModel(f->linkName());
                if(lm != nullptr)
                {
                    lm->enableNoChoice(!f->notNull());
                    cBox->setModel(lm);
                }
            }
        }
        else if(f->type() == SQLFIELD_SPECIAL)
        {
            QComboBox *cBox = (QComboBox*)i.value();
            cBox->clear();
            cBox->insertItems(0,SqlField::getSpecialTypeList(f->linkName()));
        } else
             ((QLineEdit*)i.value())->setText("");
    }
}

int AbstractAddItemWidget::getCurDatumID()
{
    if(m_curDatum.isValid())
        return m_curDatum.getID();

    return -1;
}

