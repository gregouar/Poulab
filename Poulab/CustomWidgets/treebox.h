/** This custom version of QComboBox allow to ask the user to choose an item in a Tre. **/

#ifndef TREEBOX_H
#define TREEBOX_H

#include <QComboBox>
#include <QTreeView>

class TreeBox : public QComboBox
{
public:
    TreeBox(QWidget* parent = 0);
    bool eventFilter(QObject* object, QEvent* event);
    virtual void showPopup();
    virtual void hidePopup();
private:
    bool skipNextHide;
    QTreeView *m_view;
};

#endif // TREEBOX_H
