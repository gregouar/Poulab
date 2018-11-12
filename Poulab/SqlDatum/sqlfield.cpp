#include "sqlfield.h"

bool SqlField::INIT_SPECIAL_TYPES = false;
QMap<QString, QStringList> SqlField::SPECIAL_TYPES;

void SqlField::initSpecialTypeList()
{
    if(!SqlField::INIT_SPECIAL_TYPES)
    {
        QStringList hypolist;
        hypolist.push_back("Holotype");
        hypolist.push_back("Paratype");
        hypolist.push_back("Referred");
        hypolist.push_back("Lectotype");
        SqlField::SPECIAL_TYPES.insert("Hypodigme",hypolist);

        QStringList paritylist;
        paritylist.push_back("--None--");
        paritylist.push_back("Left");
        paritylist.push_back("Right");
        SqlField::SPECIAL_TYPES.insert("Parity",paritylist);

        QStringList complist;
        complist.push_back("Full");
        complist.push_back("Partial");
        SqlField::SPECIAL_TYPES.insert("Completeness",complist);


        SqlField::INIT_SPECIAL_TYPES = true;
    }
}

const QStringList  &SqlField::getSpecialTypeList(const QString &specialTypeName)
{
    return SPECIAL_TYPES[specialTypeName];
}

const QString &SqlField::getSpecialType(const QString &specialTypeName, int value)
{
    return SPECIAL_TYPES[specialTypeName].at(value);
}


SqlField::SqlField(SQLFIELD_TYPE type, bool notNull, QString link_name, bool treeView)
{
    m_type = type;
    m_link_name = link_name;
    m_notNull = notNull;
    m_treeView = treeView;
}



SQLFIELD_TYPE SqlField::type() const
{
    return m_type;
}

const QString &SqlField::linkName() const
{
    return m_link_name;
}

bool SqlField::notNull() const
{
    return m_notNull;
}

bool SqlField::treeView() const
{
    return m_treeView;
}

