#include "leftwidget.h"

LeftWidget::LeftWidget(QWidget *parent) :
    QWidget(parent)
{
    QSplitter *splitter = new QSplitter(Qt::Vertical, this); //新建主分割窗口，水平分割
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    m_objectTree = new QTreeWidget(this);

    splitter->addWidget(m_objectTree);

    m_objectTree->setColumnCount(2); //设置列数
    m_objectTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_objectTree->header()->setStretchLastSection(true);
    m_objectTree->setHeaderLabels(QStringList()<<tr("Wiget")<<tr("Id")); //设置头的标题
    connect(m_objectTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

void LeftWidget::addWidget(Widget *w)
{
    //添加
    int type = w->getType();
    QString name = QString("%1").arg(EnumToStr(type));
    QString id = QString("%1").arg(w->getId());
    QVariant value = (int)w;    //存指针
    switch (type) {
    case Window:
    {
        QTreeWidgetItem *win = new QTreeWidgetItem(m_objectTree, QStringList(name)); //添加子节点
        win->setIcon(0, QIcon(QString(":/%1").arg(name.toLower())));
        win->setText(1, id);
        win->setData(0, Qt::UserRole, value);
        m_curWinItem = win;
        break;
    }
    case Button:
    case Text:
    case Edit:
    case Image:
    case Line:
    case Rect:
    case Circle:
    {
        QTreeWidgetItem *child = new QTreeWidgetItem(m_curWinItem, QStringList(name)); //添加子节点
        child->setIcon(0, QIcon(QString(":/%1").arg(name.toLower())));
        child->setText(1, id);
        child->setData(0, Qt::UserRole, value);
        m_curWinItem->addChild(child);
        m_curWinItem->setExpanded(true);
        break;
    }
    default:
        break;
    }

    currentItemChanged(w);
}
void LeftWidget::currentItemChanged(Widget *w)
{
    //先遍历，是否已经添加该w
    QTreeWidgetItemIterator it(m_objectTree);
    while (*it) {
        QTreeWidgetItem *item = (*it);
        Widget *pItem = (Widget *)(item->data(0, Qt::UserRole).toInt());
        if (pItem == w){
            m_objectTree->setCurrentItem(item);
            //同时切换记录的当前窗口
            if (item->parent()==NULL){
                m_curWinItem = item;
            }
            return;
        }
        ++it;
    }
}

void LeftWidget::currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (!current) return;
    Widget *pItem = (Widget *)(current->data(0, Qt::UserRole).toInt());
    pItem->setFocus();
}

void LeftWidget::removeWidgetSlt(Widget *w)
{
    //先遍历，是否已经添加该w
    QTreeWidgetItemIterator it(m_objectTree);
    while (*it) {
        QTreeWidgetItem *item = (*it);
        Widget *pItem = (Widget *)(item->data(0, Qt::UserRole).toInt());
        if (pItem == w){
            if(item->childCount() > 0){
                for(int i = 0; i < item->childCount(); i ++){
                    delete item->child(i);
                }
            }
            delete item;
        }
        ++it;
    }
}

