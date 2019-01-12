#include "sciapislua.h"

SciAPIsLua::SciAPIsLua(QsciLexer *lexer) : QsciAPIs(lexer)
{
    initKeyWords();
}

SciAPIsLua::SciAPIsLua(char *words, QsciLexer *lexer) : QsciAPIs(lexer)
{
    QStringList strList = QString(QLatin1String(words)).split(" ");
    for(int i=0;i<strList.count();i++){
        this->add(strList[i]);
    }
    initKeyWords();
}

void SciAPIsLua::initKeyWords()
{
    this->add(QString("move"));
    this->add(QString("moive"));
    this->add("test1?1(double,int,int) Extra info");
    this->add("test2?1(double)");
    this->add("test3?1(const char *s, int)");
    this->add("Foo::test4?1(const char *s, int)");
    this->add("Foo::test5?1(int)");
    this->add("Foo::test6?1(std::string)");
    if(this->load(QString(":/keywords")));
        //qDebug()<<"读取成功";
    //else
        //qDebug()<<"读取失败";
    this->prepare();
}
