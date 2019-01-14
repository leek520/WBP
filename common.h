#ifndef COMMON_H
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
#include <QScrollBar>
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
#include <QProgressBar>
#include <QDrag>
#include <QToolButton>

#define CHAR_START_UNICODE    0x4e00

#define START_ADDR_SDRAM_WIDGET  0xa0300000
#define START_ADDR_FLASH_WIDGET  0x100000

#define START_ADDR_SDRAM_STRING  0xa043F000
#define START_ADDR_FLASH_STRING  0x23F000

#define START_ADDR_SDRAM_LUA  0xa045F000
#define START_ADDR_FLASH_LUA  0x25F000

#define START_ADDR_SDRAM_IMAGE  0xa047E000
#define START_ADDR_FLASH_IMAGE  0x27E000

#define START_ADDR_SDRAM_CHAR  0xa04BD000
#define START_ADDR_FLASH_CHAR  0x2BD000

#define START_ADDR_SDRAM_FONT  0xa057D000
#define START_ADDR_FLASH_FONT  0x37D000

#define LAN_NUM         2
#define VAR_BUF_LEN		128

#define INVALID_COLOR 0x80000000

#define CAL_ID(parent, index)   ((parent<<11) | index)  //父窗体最多可容纳2^10=1024个子窗体
/************??????*************/
//链表结构
struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};
typedef enum _eWidgetType
{
    Window = 0,
    Button,
    Text,
    Edit,

    Image = 10,
    Line,
    Rect,
    Circle,
}WidgetType;

typedef enum _eTextType
{
    String,
    RegVaule,
    StringList,
}TextType;
typedef enum _eWriteType
{
    FixValue,
    Addiction,
    Reduction,
}WriteType;
typedef enum _eRegType
{
    I8,
    U8,
    I16,
    U16,
    I32,
    U32,
    F32,
    D64,
}RegType;
typedef struct {
  uchar XSize;
  uchar XDist;
  uchar BytesPerLine;
  uchar *pData;
}GUI_CHARINFO;

typedef struct GUI_FONT_PROP {
  ushort First;                                              /* First character               */
  ushort Last;                                               /* Last character                */
  GUI_CHARINFO *paCharInfo;     /* Address of first character    */
  struct GUI_FONT_PROP *pNext;          /* Pointer to next               */
} GUI_FONT_PROP;

struct GUI_FONT {
  void * pfDispChar;
  void * pfGetCharDistX;
  void * pfGetFontInfo;
  void * pfIsInFont;
  void * pfGetCharInfo;
  void * pafEncode;
  uchar YSize;
  uchar YDist;
  uchar XMag;
  uchar YMag;
  union {
    void * pFontData;
    void * pMono;
    void * pProp;
    void * pPropExt;
  } p;
  uchar Baseline;
  uchar LHeight;     /* Height of a small lower case character (a,x) */
  uchar CHeight;     /* Height of a small upper case character (A,X) */
};
/*********»ù´¡ÐÅÏ¢½á¹¹************/
typedef struct _tBasePara
{
    struct list_head list;
    ushort x0;
    ushort y0;
    ushort xsize;
    ushort ysize;
    ushort Id;
    uchar type;
    char resv;
}BasePara;
/*********ÎÄ±¾ÐÅÏ¢½á¹¹************/
typedef struct _tTextPara
{
    uchar type;
    uchar resv;
    ushort alignment;
    GUI_FONT *font;
    int color;

    char *string[LAN_NUM];
    ushort maxNum;
    ushort maxLen;

    uchar totLen;
    uchar dotLen;
    ushort regAddress;
}TextPara;
typedef struct _tOptRegPara
{
    ushort regAddress;
    uchar bitAddress;
    uchar regType;
    ushort valueType;
    ushort value;
}OptRegPara;    //2bytes
typedef struct {
  ushort XSize;
  ushort YSize;
  ushort BytesPerLine;
  ushort BitsPerPixel;
  uchar * pData;
  int pPal;
  int pMethods;
}GUI_BITMAP;

typedef enum{
    GUI_DRAW_BMP565,
    GUI_DRAW_RLE16,
}ImageMethods;

typedef struct {
    struct list_head list;
    ushort x;
    ushort y;
    GUI_BITMAP *GUI_Image;
}ImageInfo;

typedef struct {
    struct list_head list;
    int lineColor;
    int fillColor;
    ushort x;
    ushort y;
    ushort width;
    ushort height;
    uchar radius;
    uchar isFill;
    uchar lineType;
    uchar lineWidth;
}GraphInfo;
typedef struct _tTimerPara
{
        ushort Id;
        ushort time;	//ms
}TimerPara;
/*********´°ÌåÐÅÏ¢½á¹¹************/
typedef struct _tWindowInfo
{
    BasePara base;
    int BkColor[1];
    TimerPara timer;
    struct list_head childList;
    struct list_head imageList;
    struct list_head graphList;
}WindowInfo;    //8*4byte

/*********°´Å¥ÐÅÏ¢½á¹¹************/
typedef struct _tButtonInfo
{
    BasePara base;
    int BkColor[3];
    TextPara text;
    OptRegPara optReg;
}ButtonInfo;    //12*4byte
/*********ÎÄ±¾¿òÐÅÏ¢½á¹¹************/
typedef struct _tTextInfo
{
    BasePara base;
    int BkColor[1];
    TextPara text;
}TextInfo;      //9*4byte
/*********ÊäÈë¿òÐÅÏ¢½á¹¹************/
typedef struct _tEditInfo
{
    BasePara base;
    int BkColor[2];
    TextPara text;
    uchar maxLen;
    char resv[3];
}EditInfo;      //11*4byte

typedef struct _tMacroInfo
{
    struct list_head list;
    OptRegPara optReg;
    char *content;
}MacroInfo;

/************双向循环链表*************/

#define __compiler_offsetof(a,b)  __builtin_offsetof(a,b)

#undef offsetof  //取消先前的任何定义，可以保证下面的定义生效
#ifdef __compiler_offsetof
//计算member在type中的位置
#define offsetof(type, member)  (size_t)(&((type*)0)->member)
//根据member的地址获取type的起始地址
#define container_of(ptr, type, member) ({          \
         const typeof(((type *)0)->member)*__mptr = (ptr);    \
     (type *)((char *)__mptr - offsetof(type, member)); })
#endif


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
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}
//获取宿主对象地址，再将它转换为宿主数据结构类型的指针。
#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) list_entry((ptr)->next, type, member)
//前向遍历
#define list_for_each(pos, head) \
       for (pos = (head)->next;pos != (head); pos = pos->next)
//后向遍历
#define list_for_each_prev(pos, head) \
       for (pos = (head)->prev;pos != (head); pos = pos->prev)
/******************************************************************************
* @brief :链表遍历
* 如果在遍历过程中，包含有删除或移动当前链接节点的操作，由于这些操作会修改遍历指针，这样会导致遍历的中断
* 这种情况下，必须使用list_for_each_safe宏，在操作之前将遍历指针缓存下来
* 在for循环中n暂存pos下一个节点的地址，避免因pos节点被释放而造成的断链。
* 也就是说你可以遍历完当前节点后将其删除，同时可以接着访问下一个节点，
* 遍历完毕后就只剩下一个头节点。这就叫safe。十分精彩。典型用途是多个进程等待在同一个等待队列上，
* 若事件发生时唤醒所有进程，则可以唤醒后将其依次从等待队列中删除。
* @author:leek
* @date  :2018/10/10
* @para  :
* @return:
*******************************************************************************/
#define list_for_each_safe(pos, n, head) \
       for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)
// 宿主对象前向遍历
#define list_for_each_entry(pos, head, member) \
       for (pos = list_entry((head)->next, typeof(*pos), member); \
            &pos->member != (head);  \
            pos = list_entry(pos->member.next, typeof(*pos), member))
// 宿主对象后向遍历
#define list_for_each_entry_reverse(pos, head, member) \
       for (pos = list_entry((head)->prev, typeof(*pos), member); \
            &pos->member != (head);     \
            pos = list_entry(pos->member.prev, typeof(*pos), member))

#define list_prepare_entry(pos, head, member) \
       ((pos) ? (pos) : list_entry(head, typeof(*pos), member))
// 此时不是从头节点开始遍历的，但仍然是以头节点为结束点的，即没有遍历完整个链表。
#define list_for_each_entry_continue(pos, head, member)   \
       for (pos = list_entry(pos->member.next, typeof(*pos), member);  \
            &pos->member != (head);  \
            pos = list_entry(pos->member.next, typeof(*pos), member))
//它们要求调用者另外提供一个与pos同类型的指针n，在for循环中暂存pos下一个节点的地址，避免因pos节点被释放而造成的断链。
#define list_for_each_entry_safe(pos, n, head, member) \
       for (pos = list_entry((head)->next, typeof(*pos), member),  \
            n = list_entry(pos->member.next, typeof(*pos), member); \
            &pos->member != (head);   \
            pos = n, n = list_entry(n->member.next, typeof(*n), member))

#define list_for_each_entry_safe_continue(pos, n, head, member) \
       for (pos = list_entry(pos->member.next, typeof(*pos), member), \
              n = list_entry(pos->member.next, typeof(*pos), member); \
            &pos->member != (head);     \
            pos = n, n = list_entry(n->member.next, typeof(*n), member))

#endif // COMMON_H
