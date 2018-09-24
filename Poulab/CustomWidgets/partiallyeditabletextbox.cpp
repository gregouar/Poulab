#include "partiallyeditabletextbox.h"

#include <QDebug>

PartiallyEditableTextBox::PartiallyEditableTextBox(QWidget* parent):
    QPlainTextEdit(parent)
{
    m_old_length = 0;

    m_highlighter = new Highlighter(&m_nonEditableList, this->document());

    connect(this->document(), SIGNAL(contentsChange(int,int,int)),
            this, SLOT(handleTextChanged(int,int,int)));
}

void PartiallyEditableTextBox::clear()
{
    m_old_length = 0;
    m_nonEditableList.clear();
    QPlainTextEdit::clear();
}

void PartiallyEditableTextBox::changeNonEditableText(const NonEditablePart* target, const QString& newText)
{
    NonEditablePart* part = this->findNonEditablePart(target);
    if(part != nullptr)
    {
        int old_length = part->length();
        int move_value = newText.length() - old_length;

        QTextCursor c = this->textCursor();
        c.setPosition(part->startPosition(), QTextCursor::MoveAnchor);
        c.setPosition(part->endPosition(), QTextCursor::KeepAnchor);
        this->setTextCursor(c);

        part->setContent(newText);

        this->blockSignals(true);
        this->insertPlainText(newText);
        this->blockSignals(false);

        this->moveNonEditableParts(part->startPosition(),move_value,true);
    }
}

void PartiallyEditableTextBox::appendString(const QString &text)
{
    QPlainTextEdit::moveCursor (QTextCursor::End);
    QPlainTextEdit::insertPlainText (text);
    QPlainTextEdit::moveCursor (QTextCursor::End);
}

const NonEditablePart* PartiallyEditableTextBox::addNonEditableText(QString newText, int p)
{
    if(p == -1)
        p = this->toPlainText().length();

    m_nonEditableList.push_back(NonEditablePart (p,newText));
    m_old_length += newText.length();

    this->blockSignals(true);
    this->appendString(newText);
    this->blockSignals(false);

    return &m_nonEditableList.back();
}

void PartiallyEditableTextBox::removeNonEditableText(const NonEditablePart* target)
{
    int left = target->startPosition();
    int right = target->endPosition();
    this->moveNonEditableParts(target->startPosition(),-target->length());

    for(int i = 0 ; i < m_nonEditableList.size() ; ++i)
    {
        if(&m_nonEditableList[i] == target)
        {
            QTextCursor c = this->textCursor();
            c.setPosition(left, QTextCursor::MoveAnchor);
            c.setPosition(right, QTextCursor::KeepAnchor);

            m_nonEditableList.removeAt(i);

            this->blockSignals(true);
            c.removeSelectedText();
            this->blockSignals(false);
        }
    }
}


NonEditablePart* PartiallyEditableTextBox::findNonEditablePart(const NonEditablePart* part)
{
    for(int i = 0 ; i < m_nonEditableList.size() ; ++i)
    {
        if(&m_nonEditableList[i] == part)
            return &m_nonEditableList[i];
    }
    return nullptr;
}

void PartiallyEditableTextBox::moveNonEditableParts(int pos, int value, bool strict)
{
    for(int i = 0 ; i < m_nonEditableList.size() ; ++i)
    {
        NonEditablePart *part = &m_nonEditableList[i];
        if( part->startPosition() > pos || (!strict && part->startPosition() == pos))
            part->move(value);
    }

    m_highlighter->rehighlight();
}

void PartiallyEditableTextBox::handleTextChanged(int pos, int removed, int added)
{
    if(!this->signalsBlocked()){

    this->blockSignals(true);

    QTextCursor c = this->textCursor();
    c.setPosition(pos, QTextCursor::MoveAnchor);
    c.setPosition(pos+added, QTextCursor::KeepAnchor);
    int curPos = pos;
    QString addedText = c.selectedText();
    c.removeSelectedText();

    QString textToAdd = "";

    for(int i = 0 ; i < m_nonEditableList.size() ; ++i)
    {
        NonEditablePart *p = &m_nonEditableList[i];

        if(p->startPosition() >= pos+removed)
        {
            p->move(added-removed);
        }
        else
        {
            if(p->startPosition() < pos && p->endPosition() >= pos)
            {
                int diff = pos - p->startPosition();
                pos = p->startPosition();
                removed += diff;
                curPos = pos;

                c.setPosition(pos, QTextCursor::MoveAnchor);
                c.setPosition(pos+diff, QTextCursor::KeepAnchor);
                c.removeSelectedText();
            }

            if((p->endPosition() > pos && p->endPosition() <= pos+removed)
             ||(p->startPosition() >= pos && p->startPosition() < pos+removed)
             ||(p->startPosition() <= pos && p->endPosition() >= pos+removed))
            {
                if(p->endPosition() > pos+removed)
                {
                    int toRemove = (p->endPosition()-pos-removed);
                    c.setPosition(pos, QTextCursor::MoveAnchor);
                    c.setPosition(pos+toRemove, QTextCursor::KeepAnchor);
                    c.removeSelectedText();
                    removed += toRemove;
                }
                textToAdd += p->content();
                added += p->length();
                p->setStartPosition(curPos);
                curPos += p->length();
            }
        }
    }

    textToAdd += addedText;
    c.setPosition(pos, QTextCursor::MoveAnchor);
    c.insertText(textToAdd);

    m_highlighter->rehighlight();
    this->blockSignals(false);
    }
}


/// ************************************* ///
/// Highlighter                           ///
/// ************************************* ///


Highlighter::Highlighter(const QList<NonEditablePart> *l, QTextDocument *parent):
    QSyntaxHighlighter(parent)
{
    m_nonEditableList = l;
}

void Highlighter::highlightBlock(const QString &text)
{
    Q_UNUSED(text);

    QTextCharFormat format;
    format.setForeground(Qt::darkMagenta);
    format.setFontWeight(QFont::Bold);
    for(int i = 0 ; i < m_nonEditableList->size() ; ++i)
    {
        this->setFormat(m_nonEditableList->at(i).startPosition(),
                        m_nonEditableList->at(i).length(),
                        format);
    }
}

/// ************************************* ///
///  NonEditablePart                      ///
/// ************************************* ///

NonEditablePart::NonEditablePart(int p, const QString &content)
{
    m_startPos = p;
    m_content = content;
}

int NonEditablePart::startPosition() const
{
    return m_startPos;
}

int NonEditablePart::endPosition() const
{
    return m_startPos+this->length();
}

int NonEditablePart::length() const
{
    return m_content.size();
}

const QString &NonEditablePart::content() const
{
    return m_content;
}

bool NonEditablePart::isInside(int p, bool strict) const
{
    int l = this->startPosition() + strict;
    int r = this->endPosition() - strict;
    return (p >= l && p <= r);
}

void NonEditablePart::move(int p)
{
    this->setStartPosition(this->startPosition() + p);
}

void NonEditablePart::setStartPosition(int p)
{
    m_startPos = p;
}

void NonEditablePart::setContent(const QString &content)
{
    m_content = content;
}









