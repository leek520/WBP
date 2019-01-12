#include "qeditor.h"
#include "ui_qeditor.h"
#include "../window/publicvar.h"

QEditor::QEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QEditor)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);

    connect(ui->tableWidget, SIGNAL(currentCellChanged(int,int,int,int)),
            this, SLOT(currentChanged(int,int,int,int)));
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(itemChanged(QTableWidgetItem*)));
    on_action_New_triggered();

    ui->regType->addItems(PV->getEnumProperty("WriteRegType"));
    ui->triggerType->addItems(PV->getEnumProperty("TriggerType"));
}

QEditor::~QEditor()
{
    delete ui;
}

QList<QEditor::Macro> *QEditor::getMacroList()
{
    return &m_macroList;
}

void QEditor::showEditor()
{
    if (ui->tableWidget->rowCount() != m_macroList.count()){
        ui->tableWidget->setRowCount(m_macroList.count());
        for(int i=0;i<m_macroList.count();i++){
            QTableWidgetItem *item = new QTableWidgetItem(m_macroList[i].name);
            item->setCheckState((m_macroList[i].isUsed==0?(Qt::Unchecked):(Qt::Checked)));
            ui->tableWidget->setItem(i, 0, item);
        }
        openItem(0);
        ui->tableWidget->setCurrentCell(0,0);
    }
    show();
}

void QEditor::currentChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if ((currentRow >= m_macroList.count()) ||
        (previousRow >= m_macroList.count())||
        (currentRow < 0) || (previousRow < 0))
        return;

    saveItem(previousRow);

    openItem(currentRow);
}

void QEditor::itemChanged(QTableWidgetItem *item)
{
    int row = item->row();
    m_macroList[row].isUsed = item->checkState();
    m_macroList[row].name = item->text();

}

void QEditor::saveItem(int row)
{
    if (row >= m_macroList.count()) return;
    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    m_macroList[row].isUsed = item->checkState();
    m_macroList[row].name = item->text();
    m_macroList[row].content = ui->codeEditor->text();
    m_macroList[row].mark = "";
    m_macroList[row].regAddress = ui->regAddress->value();
    m_macroList[row].bitAddress = ui->bitAddress->value();
    m_macroList[row].regType = ui->regType->currentIndex();
    m_macroList[row].tirggerType = ui->triggerType->currentIndex();
}

void QEditor::openItem(int row)
{
    if (row >= m_macroList.count()) return;
    ui->codeEditor->setText(m_macroList[row].content);
    ui->regAddress->setValue(m_macroList[row].regAddress);
    ui->bitAddress->setValue(m_macroList[row].bitAddress);
    ui->regType->setCurrentIndex(m_macroList[row].regType);
    ui->triggerType->setCurrentIndex(m_macroList[row].tirggerType);
    ui->tableWidget->item(row, 0)->setCheckState((m_macroList[row].isUsed==0?(Qt::Unchecked):(Qt::Checked)));
    ui->tableWidget->item(row, 0)->setText(m_macroList[row].name);
}


void QEditor::on_action_Font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->codeEditor->getCurrentFont(), this, "font");
    if(ok)
    {
        ui->codeEditor->setCurrentFont(font);   //current可以undo
    }
}

void QEditor::on_action_New_triggered()
{
    int index = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(index);


    Macro newMacro;
    newMacro.regAddress = 0;
    newMacro.bitAddress = 0;
    newMacro.regType = 0;
    newMacro.tirggerType = 0;
    newMacro.name = "new macro";
    newMacro.isUsed = true;
    newMacro.mark = "";
    m_macroList.append(newMacro);

    QTableWidgetItem *item = new QTableWidgetItem(newMacro.name);
    item->setCheckState(Qt::Checked);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    ui->tableWidget->setItem(index, 0, item);
    ui->tableWidget->setCurrentCell(index, 0);
}

void QEditor::on_regType_currentIndexChanged(int index)
{
    if (index == 0){
        ui->bitAddress->setEnabled(false);
    }else{
        ui->bitAddress->setEnabled(true);
    }
}

void QEditor::closeEvent(QCloseEvent *event)
{
    saveItem(ui->tableWidget->currentRow());
    event->accept();
}

void QEditor::on_action_Build_triggered()
{
    QString outMsg = "";
    char *inStr;
    const char *outStr;
    QByteArray ba = ui->codeEditor->text().toLatin1();
    inStr = ba.data();
    lua_State* L;
    L=luaL_newstate();
    luaopen_base(L);    //调用print使用
    if (luaL_loadstring(L, inStr) != LUA_OK){
        outStr = lua_tostring(L,-1);
        QString tmpStr = QString(QLatin1String(outStr));
        tmpStr.replace(QRegExp("\\[.+\\]:"), "Line ");
        outMsg += tmpStr + "\n";
    }else{
        outMsg += "Build success!\n";
        if (lua_pcall(L,0,0,0) != LUA_OK){
            outStr = lua_tostring(L,-1);
            QString tmpStr = QString(QLatin1String(outStr));
            tmpStr = tmpStr.replace(QRegExp("\\[.+\\]:"), "Line ");
            outMsg += tmpStr  + "\n";
        }else{
           outMsg += "Excute success!\n";
        }
    }
    lua_close(L);
    ui->outText->setText(outMsg);
}

