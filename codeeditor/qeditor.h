#ifndef QEDITOR_H
#define QEDITOR_H

#include <QMainWindow>
#include <QFontDialog>
#include <QTableWidgetItem>
#include <QProcess>

#include <lua/lua.hpp>
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include <windows.h>
#define IS(s)	(strcmp(argv[0],s)==0)
namespace Ui {
class QEditor;
}

class QEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit QEditor(QWidget *parent = 0);
    ~QEditor();
    struct Macro{
        ushort regAddress;
        ushort bitAddress;
        ushort regType;
        ushort tirggerType;
        bool isUsed;
        QString mark;
        QString name;
        QString content;
    };
    QList<Macro> *getMacroList();
    void showEditor();
private slots:
    void currentChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void itemChanged(QTableWidgetItem *item);
    void saveItem(int row);
    void openItem(int row);

    void on_action_Font_triggered();

    void on_action_New_triggered();

    void on_regType_currentIndexChanged(int index);
    void on_action_Build_triggered();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::QEditor *ui;
    QList<Macro> m_macroList;
};

#endif // QEDITOR_H
