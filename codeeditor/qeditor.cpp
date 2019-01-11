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

void QEditor::currentChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if ((currentRow >= m_macroList.count()) ||
        (previousRow >= m_macroList.count())||
        (currentRow < 0) || (previousRow < 0))
        return;
    QTableWidgetItem *item = ui->tableWidget->item(previousRow, previousColumn);
    m_macroList[previousRow].isUsed = item->checkState();
    m_macroList[previousRow].name = item->text();
    m_macroList[previousRow].content = ui->codeEditor->text();
    m_macroList[previousRow].mark = "";
    m_macroList[previousRow].regAddress = ui->regAddress->value();
    m_macroList[previousRow].bitAddress = ui->bitAddress->value();
    m_macroList[previousRow].regType = ui->regType->currentIndex();
    m_macroList[previousRow].tirggerType = ui->triggerType->currentIndex();

    item = ui->tableWidget->item(currentRow, currentColumn);
    ui->codeEditor->setText(m_macroList[currentRow].content);

    ui->regAddress->setValue(m_macroList[currentRow].regAddress);
    ui->bitAddress->setValue(m_macroList[currentRow].bitAddress);
    ui->regType->setCurrentIndex(m_macroList[currentRow].regType);
    ui->triggerType->setCurrentIndex(m_macroList[currentRow].tirggerType);
}

void QEditor::itemChanged(QTableWidgetItem *item)
{
    int row = item->row();
    m_macroList[row].isUsed = item->checkState();
    m_macroList[row].name = item->text();
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
