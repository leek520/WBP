#ifndef QSCIAPISLUA_H
#define QSCIAPISLUA_H
#include <QDebug>

#include <Qsci/qsciapis.h>
class SciAPIsLua : public QsciAPIs
{
    Q_OBJECT
public:
    explicit SciAPIsLua(QsciLexer *lexer);
    SciAPIsLua(char *words, QsciLexer *lexer);
signals:

public slots:
private:
    void initKeyWords();
};

#endif // QSCIAPISLUA_H
