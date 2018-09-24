/** An SqlField represent a column in a table. Our interface accept different kind of field type.
 * In particular, SQLFIELD_LINK should contains the id of a record in a related table (precised as link_name).
 * If the link_name is the same as the name of the table, it is better to activate treeView = true.
 * SQLFIELD_SPECIAL is a multiple choice type of data, that is define in the static method initSpecialTypeList().
 **/

#ifndef SQLFIELD_H
#define SQLFIELD_H

#include <QString>
#include <QMap>
#include <QStringList>

enum SQLFIELD_TYPE {
    SQLFIELD_TEXT,
    SQLFIELD_REAL,
    SQLFIELD_INTEGER,
    SQLFIELD_LINK,
    SQLFIELD_SPECIAL,
    SQLFIELD_SORTER,
};

class SqlField
{
public:
    SqlField(SQLFIELD_TYPE type, bool notNull, QString link_name = "", bool treeView = false);

    SQLFIELD_TYPE type() const;
    const QString &linkName() const;
    bool notNull() const;
    bool treeView() const;

    static void initSpecialTypeList();
    static const QStringList &getSpecialTypeList(const QString &);
    static const QString &getSpecialType(const QString &type, int value);


private:
    SQLFIELD_TYPE   m_type;
    QString         m_link_name;
    bool            m_notNull;
    bool            m_treeView;

    static bool INIT_SPECIAL_TYPES;
    static QMap<QString, QStringList> SPECIAL_TYPES;
};

#endif // SQLFIELD_H
