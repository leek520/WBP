#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QWidget>
#include <QPainter>
#include <QTextBlock>
#include <QResizeEvent>
#include <QPlainTextEdit>
#include <QScrollBar>
class LineNumberArea;

#include "completer.h"
#include "highlighter.h"
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    CodeEditor(QWidget *parent = 0);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setTextForeColor(QColor col);
    void setTextBackColor(QColor col);
    void setTextFont(QFont m_font);
    void setTextFont(int fontsize);
    void setHighLightColor(QColor col);
protected:
    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void focusInEvent(QFocusEvent *e);
    void wheelEvent(QWheelEvent *e);
private:
    void setCompleter(QCompleter *c);
    QString textUnderCursor() const;
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void insertCompletion(const QString &completion);
private:
    QWidget *lineNumberArea;
    QCompleter *completer;
    Highlighter *highlighter;

    QFont m_font;
    QColor m_highLightColor;
};
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

#endif // CODEEDITOR_H
