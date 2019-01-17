#include "codeeidtor.h"

CodeEidtor::CodeEidtor(QWidget *parent) :
    QsciScintilla(parent)
{
    memset(m_keyWords, 0, 512);

    setUtf8(true);  //支持中文

    setAutoCompletionSource(QsciScintilla::AcsAll);    //自动补全所以地方出现的
    setAutoCompletionCaseSensitivity(false);   //设置自动补全大小写敏感
    setAutoCompletionThreshold(1);             //输入1字符就会出现自动补全的提示
    setAutoCompletionUseSingle(QsciScintilla::AcusNever);
    setCallTipsStyle(QsciScintilla::CallTipsContext);
    setAutoCompletionFillupsEnabled(true);
    //setCallTipsBackgroundColor();
    //setCallTipsForegroundColor();
    //setCallTipsHighlightColor();

//    //whitespace
//    setWhitespaceVisibility(QsciScintilla::WsInvisible);
//    setWhitespaceSize(2);
//    //mesure line
//    setEdgeMode(QsciScintilla::EdgeLine);
//    setEdgeColumn(150);
//    setEdgeColor(QColor("#BBB8B5"));

    //table relative
    setAutoIndent(true);    //开启自动缩进
    setTabIndents(true);
    setTabWidth(4);
    setIndentationsUseTabs(true);
    setIndentationWidth(4);
    setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);//设置缩进的显示方式
    setBackspaceUnindents(true);

    //显示选中的行号
    setCaretLineVisible(true);
    //显示选中行号的背景色
    setCaretLineBackgroundColor(Qt::lightGray);
    //setCaretForegroundColor(QColor("white"))
    //setSelectionBackgroundColor(QColor("#606060"));
    //setSelectionForegroundColor(QColor("#FFFFFF"));

    //设置括号匹配
    setBraceMatching(QsciScintilla::SloppyBraceMatch);  //稀松匹配
    setMatchedBraceBackgroundColor(Qt::magenta);

    setMarginsArea();
    lineNumberChanged();
    connect(this, SIGNAL(linesChanged()), this, SLOT(lineNumberChanged()));
}

void CodeEidtor::setCurrentFont(QFont font)
{
    setFont(font);
    m_textLexer->setDefaultFont(font);
    m_textLexer->setFont(font);
    QFontMetrics fm(font);
    int space = 10 + fm.width(QString::number(lines()));
    setMarginWidth(0, space);   //设置页边宽度

}

const QFont CodeEidtor::getCurrentFont()
{
    return m_textLexer->defaultFont(-1);
}

void CodeEidtor::setCurrentLine(int line)
{
    setCursorPosition(line, 0);
}

void CodeEidtor::addUserKeywords(const char *keywords)
{
    strcat(m_keyWords, keywords);
}

void CodeEidtor::initLexer()
{
    //词法分析器
    m_textLexer = new SciLexerLua(m_keyWords);

    setFont(QFont("Courier", 20, QFont::Normal));
    m_textLexer->setFont(font());
    setLexer(m_textLexer);
}

void CodeEidtor::setMarginsArea()
{
    //行号显示区域
    setMarginsBackgroundColor(QColor("#bbfaae"));
    //setMarginsFont();
    setMarginType(0, QsciScintilla::NumberMargin);  //设置编号为0的页边显示行号
    setMarginLineNumbers(0, true);  //对该页边启用行号
    setMarginWidth(0, 30);
    //断点设置区域
    setMarginType(1, QsciScintilla::SymbolMargin);
    setMarginWidth(1,20);
    setMarginSensitivity(1, true);    //设置是否可以显示断点

    setMarginMarkerMask(1, 0x02);
    markerDefine(QsciScintilla::Circle, 1);
    setMarkerBackgroundColor(QColor("#ee1111"), 1);
    setMarginLineNumbers(1, false);
    //单步执行显示区域
    setMarginType(2, QsciScintilla::SymbolMargin);
    setMarginWidth(2, 20);
    setMarginSensitivity(2, true);
    setMarginMarkerMask(2, 0x04);
    markerDefine(QsciScintilla::RightArrow, 2);
    setMarkerBackgroundColor(QColor("#eaf593"), 2);
    setMarginLineNumbers(2, false);


    //自动折叠区域
    setFolding(QsciScintilla::CircledTreeFoldStyle, 3);
    setMarginType(3, QsciScintilla::SymbolMargin);
    setMarginWidth(3, 20);
    setMarginSensitivity(3, true);

    //marker
//    markerDefine(QsciScintilla::Minus,QsciScintilla::SC_MARKNUM_FOLDEROPEN);
//    markerDefine(QsciScintilla::Plus ,QsciScintilla::SC_MARKNUM_FOLDER);
//    markerDefine(QsciScintilla::Minus,QsciScintilla::SC_MARKNUM_FOLDEROPENMID);
//    markerDefine(QsciScintilla::Plus ,QsciScintilla::SC_MARKNUM_FOLDEREND);
    //marker define color
//    setMarkerBackgroundColor(QColor("#FFFFFF"), QsciScintilla::SC_MARKNUM_FOLDEREND);
//    setMarkerForegroundColor(QColor("#272727"), QsciScintilla::SC_MARKNUM_FOLDEREND);
//    setMarkerBackgroundColor(QColor("#FFFFFF"), QsciScintilla::SC_MARKNUM_FOLDEROPENMID);
//    setMarkerForegroundColor(QColor("#272727"), QsciScintilla::SC_MARKNUM_FOLDEROPENMID);
//    setMarkerBackgroundColor(QColor("#FFFFFF"), QsciScintilla::SC_MARKNUM_FOLDERSUB);
//    setMarkerForegroundColor(QColor("#272727"), QsciScintilla::SC_MARKNUM_FOLDERSUB);
//    setMarkerBackgroundColor(QColor("#FFFFFF"), QsciScintilla::SC_MARKNUM_FOLDER);
//    setMarkerForegroundColor(QColor("#272727"), QsciScintilla::SC_MARKNUM_FOLDER);
//    setMarkerBackgroundColor(QColor("#FFFFFF"), QsciScintilla::SC_MARKNUM_FOLDEROPEN);
//    setMarkerForegroundColor(QColor("#272727"), QsciScintilla::SC_MARKNUM_FOLDEROPEN);
//    setFoldMarginColors(QColor("#272727"),QColor("#272727"));

    connect(this, SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)),
            this, SLOT(onMarginClicked(int, int, Qt::KeyboardModifiers)));
}

void CodeEidtor::onMarginClicked(int margin, int line, Qt::KeyboardModifiers state)
{
//    markerAdd(line, margin);
//    markerAdd(line, margin+1);
}

void CodeEidtor::lineNumberChanged()
{
    //QFontMetrics fm(m_textLexer->font(-1));
    int space = 10 + fontMetrics().width(QString::number(lines()));
    setMarginWidth(0, space);   //设置页边宽度
}
