#include "bottomwidget.h"

BottomWidget::BottomWidget(QWidget *parent) : QTextEdit(parent)
{

}

void BottomWidget::insertMessage(QString msg)
{
    insertPlainText(msg + "\n");
    //移动滚动条到底部
    QScrollBar *scrollbar = verticalScrollBar();
    if (scrollbar){
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
    qApp->processEvents();
}
