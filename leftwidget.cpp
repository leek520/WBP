#include "leftwidget.h"

LeftWidget::LeftWidget(QWidget *parent) :
    QWidget(parent)
{
    QSplitter *splitter = new QSplitter(Qt::Vertical, this); //新建主分割窗口，水平分割
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    m_tree = new QTreeWidget(this);
    m_tree->setHeaderLabel("");
    m_table = new QTableWidget(this);
    splitter->addWidget(m_tree);
    splitter->addWidget(m_table);
}
