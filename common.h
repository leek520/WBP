#ifndef COMMON_H
#define COMMON_H
#include <QApplication>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QListWidget>
#include <QTextEdit>
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
#include <QDebug>


struct BaseProp
{
    ushort xPos;
    ushort yPos;
    ushort xSize;
    ushort ySize;
    QString name;
    uint backColor;
};
struct WindowPorp
{
    BaseProp baseProp;
};

#endif // COMMON_H
