#ifndef CODEEIDTOR_H
#define CODEEIDTOR_H

#include <QScrollBar>
#include <QWheelEvent>
#include <QDebug>
#include <QApplication>
#include <Qsci/qsciscintilla.h>

#include "scilexerlua.h"

class CodeEidtor : public QsciScintilla
{
    Q_OBJECT
public:
    explicit CodeEidtor(QWidget *parent = 0);
    void setCurrentFont(QFont font);
    const QFont getCurrentFont();
protected:

signals:
private:
    void setMarginsArea();
private slots:
    void onMarginClicked(int margin, int line, Qt::KeyboardModifiers state);
    void lineNumberChanged();
public slots:
private:
    SciLexerLua *m_textLexer;
};

#endif // CODEEIDTOR_H
