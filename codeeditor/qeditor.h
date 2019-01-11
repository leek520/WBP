#ifndef QEDITOR_H
#define QEDITOR_H

#include <QMainWindow>
#include <QFontDialog>
#include <QTableWidgetItem>
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
private slots:
    void currentChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void itemChanged(QTableWidgetItem *item);

    void on_action_Font_triggered();

    void on_action_New_triggered();

    void on_regType_currentIndexChanged(int index);

private:
    Ui::QEditor *ui;
    QList<Macro> m_macroList;
};

#endif // QEDITOR_H
