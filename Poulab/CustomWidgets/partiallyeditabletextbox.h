/** This custom version of QPlainTextEdit can contain bits of text that are not editable
 * by the user. These are colored in purple. If the user delete (part) of them, they will
 * be automitally rewritten before the text entered by the user.
 * An editable part of text can by dynamically changed through changeNonEditableText(..) method.
 *
 * PS : Could be improved by moving what the user add at the left of an ineditable part, when
 * more untuitive.
**/

#ifndef PARTIALLYEDITABLETEXTBOX_H
#define PARTIALLYEDITABLETEXTBOX_H

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>

class NonEditablePart
{
public:
    NonEditablePart(int , const QString &content = "");

    int startPosition() const;
    int endPosition() const;
    int length() const;
    const QString &content() const;
    bool isInside(int p, bool strict = true) const;

    void move(int);
    void setStartPosition(int);
    void setContent(const QString&);

private:
    int m_startPos;
    QString m_content;
};

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(const QList<NonEditablePart> *l, QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    const QList<NonEditablePart> *m_nonEditableList;
};

class PartiallyEditableTextBox : public QPlainTextEdit
{
    Q_OBJECT

public:
    PartiallyEditableTextBox(QWidget* parent = 0);

    void appendString(const QString &text);

    void changeNonEditableText(const NonEditablePart* target, const QString& newText);
    const NonEditablePart* addNonEditableText(QString newText, int position = -1);
    void removeNonEditableText(const NonEditablePart* target);

    void clear();

protected:
    NonEditablePart* findNonEditablePart(const NonEditablePart* );
    void moveNonEditableParts(int pos, int value, bool strict = false);

protected slots:
    void handleTextChanged(int pos, int removed, int added);

private:
    QList<NonEditablePart> m_nonEditableList;
    Highlighter *m_highlighter;

    int m_old_length;
};

#endif // PARTIALLYEDITABLETEXTBOX_H
