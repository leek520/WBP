﻿#ifndef COMMON_H
#define COMMON_H
#include <QApplication>
#include <QMainWindow>
#include <QTextCodec>
#include <QDesktopWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QScrollArea>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDockWidget>
#include <QLabel>
#include <QComboBox>
#include <QTimer>
#include <QDir>
#include <QMutex>
#include <QDateTime>
#include <QTabWidget>
#include <QFileDialog>
#include <QWidget>
#include <QMouseEvent>
#include <QTableWidget>
#include <QHeaderView>
#include <QTabWidget>
#include <QTreeWidget>
#include <QSplitter>
#include <QPushButton>
#include <QMessageBox>
#include <QDomDocument>
#include <QDebug>



#define START_ADDR_SDRAM_WIDGET  0xa0300000
#define START_ADDR_FLASH_WIDGET  0x100000

#define START_ADDR_SDRAM_STRING  0xa043F000
#define START_ADDR_FLASH_STRING  0x23F000

#define START_ADDR_SDRAM_PIC  0xa047E000
#define START_ADDR_FLASH_PIC  0x27E000

#define INVALID_COLOR 0x80000000


#define CHAR_START_UNICODE    0x4e00

/************双向循环链表*************/

//计算member在type中的位置
#define offsetof(type, member)  (size_t)(&((type*)0)->member)
//根据member的地址获取type的起始地址
#define container_of(ptr, type, member) ({          \
         const typeof(((type *)0)->member)*__mptr = (ptr);    \
     (type *)((char *)__mptr - offsetof(type, member)); })

//链表结构
struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};

static inline void init_list_head(struct list_head *list)
{
    list->prev = list;
    list->next = list;
}

static inline void __list_add(struct list_head *now, struct list_head *prev, struct list_head *next)
{
    prev->next = now;
    now->prev = prev;
    now->next = next;
    next->prev = now;
}

//从头部添加
static inline void list_add_head(struct list_head *now , struct list_head *head)
{
    __list_add(now, head, head->next);
}
//从尾部添加
static inline void list_add_tail(struct list_head *now, struct list_head *head)
{
    __list_add(now, head->prev, head);
}

static inline  void __list_del(struct list_head *prev, struct list_head *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}

static inline void list_move_head(struct list_head *list, struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add_head(list, head);
}

static inline void list_move_tail(struct list_head *list,
                   struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}
#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) list_entry((ptr)->next, type, member)

#define list_for_each(pos, head) for (pos = (head)->next; ; pos = pos->next)



typedef enum _eWidgetType
{
    Window,
    Button,
    Text,
    Edit,
}WidgetType;
/*********»ù´¡ÐÅÏ¢½á¹¹************/
typedef struct _tBasePara
{
    struct list_head node_info;//链表节点
    ushort x0;
    ushort y0;
    ushort xsize;
    ushort ysize;
    ushort Id;
    uchar type;
    char resv;
}BasePara; //20bytes
/*********ÎÄ±¾ÐÅÏ¢½á¹¹************/
typedef struct _tTextPara
{
    int alignment;
    int color;
    char *string;
}TextPara;
/*********´°ÌåÐÅÏ¢½á¹¹************/
typedef struct _tWindowInfo
{
    BasePara base;
    int BkColor[1];
    BasePara *firstChild;
}WindowInfo;

/*********°´Å¥ÐÅÏ¢½á¹¹************/
typedef struct _tButtonInfo
{
    BasePara base;
    int BkColor[3];
    TextPara text;
}ButtonInfo;
/*********ÎÄ±¾¿òÐÅÏ¢½á¹¹************/
typedef struct _tTextInfo
{
    BasePara base;
    int BkColor[1];
    TextPara text;
}TextInfo;
/*********ÊäÈë¿òÐÅÏ¢½á¹¹************/
typedef struct _tEditInfo
{
    BasePara base;
    int BkColor[2];
    uchar maxLen;
    TextPara text;
}EditInfo;


#endif // COMMON_H
