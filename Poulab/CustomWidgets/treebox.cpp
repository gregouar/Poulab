#include "treebox.h"

#include <QTreeView>
#include <QEvent>
#include <QMouseEvent>
#include <QModelIndex>
#include <QHeaderView>

//#include<QDirModel>
//#include<QDir>

TreeBox::TreeBox(QWidget* parent) : QComboBox(parent), skipNextHide(false) //Widget creation
{
    m_view = new QTreeView(this);
    m_view->header()->hide();
    m_view->viewport()->installEventFilter(this);

    this->setView(m_view);
}

bool TreeBox::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress && object == view()->viewport())
    {
           QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
           QModelIndex index = view()->indexAt(mouseEvent->pos());
           if (!view()->visualRect(index).contains(mouseEvent->pos()))
           {
                skipNextHide = true;
           }

    }
    return false;
}

void TreeBox::showPopup()
{
    m_view->expandAll();
    QComboBox::showPopup();
}

void TreeBox::hidePopup()
{
    if (skipNextHide)
            skipNextHide = false;
    else
            QComboBox::hidePopup();
}
