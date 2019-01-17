#ifndef CODEEIDTOR_H
#define CODEEIDTOR_H

#include <QScrollBar>
#include <QWheelEvent>
#include <QDebug>
#include <QApplication>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include "scilexerlua.h"

class CodeEidtor : public QsciScintilla
{
    Q_OBJECT
public:
    explicit CodeEidtor(QWidget *parent = 0);
    void setCurrentFont(QFont font);
    const QFont getCurrentFont();
    void setCurrentLine(int line);
    void addUserKeywords(const char *keywords);
    void initLexer();
protected:

signals:
private:
    void setMarginsArea();
private slots:
    void onMarginClicked(int margin, int line, Qt::KeyboardModifiers state);
    void lineNumberChanged();
public slots:
private:
    QsciLexer *m_textLexer;
    char m_keyWords[512];
};

#endif // CODEEIDTOR_H
