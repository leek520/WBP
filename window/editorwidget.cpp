#include "editorwidget.h"

EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("程序编辑器"));
    QHBoxLayout *layout = new QHBoxLayout(this);
    //CodeEditor *ce = new CodeEditor(this);
    //layout->addWidget(ce);
}
