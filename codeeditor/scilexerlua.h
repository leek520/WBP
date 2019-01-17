#ifndef SCILEXERLUA_H
#define SCILEXERLUA_H

#include "Qsci/qscilexerlua.h"
#include "sciapislua.h"
class SciLexerLua : public QsciLexerLua
{
public:
    SciLexerLua(char *words, QObject *parent = 0);
protected:
    const char *keywords(int set) const;
private:
    SciAPIsLua *m_apis;
    char *m_keywords;
};

#endif // SCILEXERLUA_H
