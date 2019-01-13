#include "qeditor.h"
#include "ui_qeditor.h"
#include "../window/publicvar.h"

QEditor::QEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QEditor)
{
    ui->setupUi(this);
    //setWindowModality(Qt::ApplicationModal);

    ui->tableWidget->setSelectionMode (QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->output->setColumnWidth(0, 40);
    ui->output->verticalHeader()->setDefaultSectionSize(20);
    ui->output->setShowGrid(false);
    ui->output->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->output->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->output->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->output, SIGNAL(cellDoubleClicked(int,int)),
            this, SLOT(outputCellClicked(int,int)));
    connect(ui->tableWidget, SIGNAL(currentCellChanged(int,int,int,int)),
            this, SLOT(currentChanged(int,int,int,int)));
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(itemChanged(QTableWidgetItem*)));
    on_action_New_triggered();

    L = openLua();

    addUserKeyWords();
    ui->codeEditor->initLexer();

    ui->regType->addItems(PV->getEnumProperty("WriteRegType"));
    ui->triggerType->addItems(PV->getEnumProperty("TriggerType"));
}

QEditor::~QEditor()
{
    closeLua(L);
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

void QEditor::outputCellClicked(int row, int col)
{
    int line = ui->output->item(row, 0)->text().toInt();
    ui->codeEditor->setCurrentLine(line-1);
    ui->codeEditor->setFocus();
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

void QEditor::addUserKeyWords()
{
    const char space[] = " ";
    const luaL_Reg *l = luaLib;
    for (; l->name != NULL; l++) {  /* fill the table with given functions */
        ui->codeEditor->addUserKeywords(l->name);
        ui->codeEditor->addUserKeywords(space);
    }
}

void QEditor::insertRecordToOutput(int row, QString key, QString value)
{
    QTableWidgetItem *item;
    item = new QTableWidgetItem(key);
    ui->output->setItem(row, 0, item);
    item = new QTableWidgetItem(value);
    ui->output->setItem(row, 1, item);
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
    QMap<int, QString> outMsgMap;

    QString allStr = ui->codeEditor->text().toLatin1();
    QStringList allStrList = allStr.split("\n");
    QString outMsg;;
    int line;
    int start = 0;
    while(!allStr.isEmpty()){
        line = syntaxCheck(allStr, outMsg, false);
        if (line < 0){
            allStr.clear();
        }else{
            start += line;
            outMsgMap.insert(start, outMsg);
            //qDebug()<<"line:"<<line;
            while(line--){
                allStrList.removeFirst();
            }
            allStr = allStrList.join("\n");
        }
    }
    //执行
    if (outMsgMap.count()==0){
        allStr = ui->codeEditor->text().toLatin1();
        line = syntaxCheck(allStr, outMsg, true);
        if (line >= 0){
            outMsgMap.insert(line, outMsg);
        }
    }

    //加入output窗口
    int cnt = outMsgMap.count();

    ui->output->setRowCount(cnt);
    QTableWidgetItem *item;
    QMap<int, QString>::iterator iter = outMsgMap.begin();
    int i = 0;
    while (iter != outMsgMap.end()){
        insertRecordToOutput(i,
                             QString("%1").arg(iter.key()),
                             iter.value());
        iter++;
        i++;
    }
    ui->output->insertRow(cnt);
    if (cnt == 0){
        insertRecordToOutput(0,
                             QString("Total:"),
                             QString("0 Errors!"));
    }else{
        insertRecordToOutput(outMsgMap.count(),
                             QString("Total:"),
                             QString("%1 Errors!").arg(outMsgMap.count()));
    }
    ui->output->scrollToBottom();
}

int QEditor::syntaxCheck(QString &in, QString &out, bool execute)
{
    int ret, line = -1;
    char *inStr;
    const char *outStr;
    QByteArray ba = in.toLatin1();
    inStr = ba.data();

    ret = luaL_loadstring(L, inStr);
    if (execute && (ret == LUA_OK)){
        ret = lua_pcall(L,0,0,0);
    }
    if (ret != LUA_OK){
        outStr = lua_tostring(L,-1);
        QString tmpStr = QString(QLatin1String(outStr));
        QRegExp rx("\\[string.+\\]:([0-9]+):");
        int pos = tmpStr.indexOf(rx);
        if (pos >= 0){
            out = tmpStr.mid(pos + rx.matchedLength());
            line = rx.cap(1).toInt();
        }
    }

    return line;
}

void QEditor::on_action_Clear_triggered()
{
    ui->output->clearContents();
}
