#include "leftwidget.h"

LeftWidget::LeftWidget(QWidget *parent) :
    QWidget(parent)
{
    QSplitter *splitter = new QSplitter(Qt::Vertical, this); //新建主分割窗口，水平分割
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    m_objectTree = new QTreeWidget(this);
    m_objectTree->setHeaderLabel("");
    m_propertyTable = new QTableWidget(this);
    splitter->addWidget(m_objectTree);
    splitter->addWidget(m_propertyTable);

    initUi();
}

void LeftWidget::initUi()
{
    m_propertyTable->setColumnCount(2); //设置列数
    m_propertyTable->setHorizontalHeaderLabels((QStringList()<<tr("属性")<<tr("值"))); //设置头的标题
    m_propertyTable->verticalHeader()->setVisible(false);
    m_propertyTable->horizontalHeader()->setStretchLastSection(true);//关键
}

void LeftWidget::setPropertyTable(int row, QString prop, QString value)
{
    QTableWidgetItem *item;
    item = new QTableWidgetItem(prop);
    m_propertyTable->setItem(row, 0, item);
    item = new QTableWidgetItem(value);
    m_propertyTable->setItem(row, 1, item);
}

void LeftWidget::currentChanged(QWidget *now)
{

}
