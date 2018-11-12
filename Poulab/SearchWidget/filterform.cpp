#include "filterform.h"

#include <QLayout>
#include <QLineEdit>
#include <QLabel>

#include "CustomWidgets/treebox.h"
#include "dbmanager.h"

FilterForm::FilterForm
        (QComboBox *tableCBox,QHBoxLayout *layout,
         const NonEditablePart *fieldNonEditablePart,
         const NonEditablePart* opNonEditablePart,
         const DbManager* db)
{
    m_tableCBox = tableCBox;
    m_fieldCBox = nullptr;
    m_fieldNonEditablePart = fieldNonEditablePart;
    m_opNonEditablePart = opNonEditablePart;

    m_layout = layout;
    m_input = nullptr;

    m_sqlField = nullptr;
    m_curSqlTable = nullptr;
    m_db = db;

    m_lastTableIndex = -1;
    m_lastFieldIndex = -1;
    m_oldValue = QVariant();

    m_opCBox = new QComboBox();
    m_opCBox->addItem("AND");
    m_opCBox->addItem("OR");

    m_fieldCBoxLayout = new QHBoxLayout();
    m_inputLayout = new QHBoxLayout();
    m_opCBoxLayout = new QHBoxLayout();

    m_layout->addLayout(m_fieldCBoxLayout,1);
    m_layout->addLayout(m_inputLayout,1);
    m_layout->addLayout(m_opCBoxLayout);

    m_opCBoxLayout->addWidget(m_opCBox);
    m_inputLayout->addWidget(new QLabel(" = "));

    connect(m_tableCBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTable(int)));
    connect(m_opCBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeOperator()));

    this->changeTable(0);
}

FilterForm::~FilterForm()
{
    askToDeleteNonEditablePart(m_fieldNonEditablePart);
    askToDeleteNonEditablePart(m_opNonEditablePart);
   /* if(m_input != nullptr)
    {
        delete m_input;
        m_input = nullptr;
    }*/
}

QString FilterForm::getTableName()
{
    return m_tableCBox->currentText();
}


void FilterForm::updateTableBox(const QList<QString> &list)
{
    if(m_tableCBox != nullptr)
    {
        QString curTable  = m_tableCBox->currentText();
        int curFieldIndex = m_fieldCBox->currentIndex();
        QVariant curValue = this->readInputValue();

        m_tableCBox->clear();
        m_tableCBox->addItems(list);

        m_tableCBox->setCurrentText(curTable);
        m_fieldCBox->setCurrentIndex(curFieldIndex);
        this->setInputValue(curValue);
    }
}


int FilterForm::lookForField(const QString &fieldName)
{
    if(m_fieldCBox != nullptr)
     return m_fieldCBox->findText(fieldName);

    return -1;
}

void FilterForm::setField(const QString &fieldName)
{
    int founded = this->lookForField(fieldName);
    if(m_fieldCBox!=nullptr)
    {
        if(founded != -1)
           m_fieldCBox->setCurrentIndex(founded);
    }
}

void FilterForm::changeTable(int newIndex)
{
    QString tableName = m_tableCBox->currentText();

    if(m_lastTableIndex != newIndex || m_curSqlTable == nullptr)
    {
        m_curSqlTable = m_db->getTable(tableName);
        generateFieldList();
        m_sqlField = nullptr;
        changeField(0);
        //inputValueChanged();
    }
}

void FilterForm::changeField(int newIndex)
{
    QString fieldName = m_fieldCBox->currentText();

    if(m_lastFieldIndex != newIndex || m_sqlField == nullptr)
    {
        m_sqlField = m_curSqlTable->getSqlField(fieldName);
        this->generateInputField();
        inputValueChanged();
    }

    m_lastFieldIndex = newIndex;
}

void FilterForm::changeOperator()
{
    QString opName = " ";
    if(m_opCBox->isVisible())
        opName = m_opCBox->currentText();

    emit askToChangeNonEditablePart(m_opNonEditablePart, opName);
}

QVariant FilterForm::readInputValue()
{
    if(m_sqlField == nullptr)
        return QVariant();

    if(m_sqlField->type() == SQLFIELD_LINK) {
        return ((QComboBox*)m_input)->currentData();
    } else if(m_sqlField->type() == SQLFIELD_SPECIAL)
    {
        return ((QComboBox*)m_input)->currentIndex();
    } else
        return ((QLineEdit*)m_input)->text();

    return QVariant();
}

void FilterForm::inputValueChanged()
{
    QString fieldName = m_fieldCBox->currentText();

    QVariant new_value = this->readInputValue();
    if(new_value.isValid())
        m_oldValue = new_value;

    QString textValue = m_oldValue.toString();
    if(m_sqlField != nullptr && m_sqlField->type() == SQLFIELD_TEXT)
    {
        if(textValue.contains('%') || textValue.contains('_'))
            textValue = " LIKE '"+textValue+"'";
        else
            textValue = " = '"+textValue+"'";
    }
    else
        textValue = " = "+textValue;

    emit askToChangeNonEditablePart(m_fieldNonEditablePart, " "+m_curSqlTable->getTableName()+"."+fieldName+textValue+" ");
}

void FilterForm::setInputValue(QVariant value)
{
    if(m_sqlField != nullptr && value.isValid())
    {
        if(m_sqlField->type() == SQLFIELD_LINK) {
            QComboBox *cBox = (QComboBox*)m_input;

            if(m_sqlField->treeView())
            {
                AbstractSqlTreeModel *tree = (AbstractSqlTreeModel*)cBox->model();
                QModelIndex founded = tree->findData(value, QModelIndex());

                QModelIndex oldRoot = cBox->rootModelIndex();
                cBox->setRootModelIndex(cBox->model()->parent(founded));
                cBox->setCurrentIndex(founded.row());
                cBox->setRootModelIndex(oldRoot);
            } else
                cBox->setCurrentIndex(cBox->findData(value));

        } else if(m_sqlField->type() == SQLFIELD_SPECIAL) {
            ((QComboBox*)m_input)->setCurrentIndex(value.toInt());
        } else
            ((QLineEdit*)m_input)->setText(value.toString());
    }
}

void FilterForm::generateFieldList()
{
    if(m_fieldCBox != nullptr)
    {
        delete m_fieldCBox;
        m_fieldCBox = nullptr;
    }

    const QMap<QString, SqlField> &fl = m_curSqlTable->getFieldTypeList();

    m_fieldCBox = new QComboBox();
    m_fieldCBox->addItems(fl.keys());
    m_fieldCBox->setCurrentIndex(0);

    m_fieldCBoxLayout->addWidget(m_fieldCBox);

    connect(m_fieldCBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeField(int)));
}

void FilterForm::generateInputField()
{
    if(m_input != nullptr)
    {
        delete m_input;
        m_input = nullptr;
    }

    if(m_sqlField != nullptr)
    {
        this->blockSignals(true);
        if(m_sqlField->type() == SQLFIELD_LINK)
        {
            QComboBox *cBox;

            if(m_sqlField->treeView())
            {
                cBox = new TreeBox();

                AbstractSqlTreeModel *im =
                        m_curSqlTable->getParentDb()->getTreeModel(m_sqlField->linkName());
                if(im != nullptr)
                {
                    im->enableNoChoice(!m_sqlField->notNull());
                    cBox->setModel(im);
                    connect(im, SIGNAL(modelReset()), this, SLOT(modelReset()));
                }
            } else {
                cBox = new QComboBox();

                AbstractSqlListModel *lm =
                        m_curSqlTable->getParentDb()->getListModel(m_sqlField->linkName());
                if(lm != nullptr)
                {
                    lm->enableNoChoice(!m_sqlField->notNull());
                    cBox->setModel(lm);
                    connect(lm, SIGNAL(modelReset()), this, SLOT(modelReset()));
                }
            }
            connect(cBox,SIGNAL(currentIndexChanged(int)),this,SLOT(inputValueChanged()));
            m_input = cBox;
            this->setInputValue(0);
        }
        else if(m_sqlField->type() == SQLFIELD_SPECIAL)
        {
            QComboBox *cBox = new QComboBox();
            cBox->clear();
            cBox->insertItems(0,SqlField::getSpecialTypeList(m_sqlField->linkName()));
            connect(cBox,SIGNAL(currentIndexChanged(int)),this,SLOT(inputValueChanged()));
            m_input = cBox;
            this->setInputValue(0);
        } else {
            QLineEdit *lineEdit = new QLineEdit();
            connect(lineEdit,SIGNAL(textEdited(QString)),this,SLOT(inputValueChanged()));
            m_input = lineEdit;
            this->setInputValue("");
        }

        m_inputLayout->addWidget(m_input,1);
        this->blockSignals(false);
    }
}

void FilterForm::setEnableOperatorCBox(bool b)
{
    m_opCBox->setVisible(b);

    this->changeOperator();
}

void FilterForm::modelReset()
{
    if(!this->signalsBlocked())
        this->setInputValue(m_oldValue);
}
