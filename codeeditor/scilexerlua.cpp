﻿#include "scilexerlua.h"

SciLexerLua::SciLexerLua(QObject *parent) :
    QsciLexerLua(parent)
{
    setFont(QFont("Times", 32, QFont::Normal));
    //设置代码提示：自动补全的字符串和补全方式
    m_apis = new SciAPIsLua(this);

//    setColor(QColor(Qt::green), QsciLexerLua::LineComment);    //设置自带的注释行为绿色
//    setColor(QColor(Qt::red), QsciLexerLua::KeywordSet5);   //设置自定义关键字的颜色为红色
}
