#include "propertydialog.h"
#include "ui_propertydialog.h"

PropertyDialog::PropertyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertyDialog)
{
    ui->setupUi(this);
    m_title = this->windowTitle();

    //设置表头
    ui->textList->horizontalHeader()->setVisible(true);
    ui->textList->setColumnCount(LAN_NUM);
}

PropertyDialog::~PropertyDialog()
{
    delete ui;
}

void PropertyDialog::showDialog(Widget *w)
{
    m_widget = w;
    QString name = EnumToStr(w->getType());
    switch (w->getType()) {
    case Window:
        ui->tab_2->setEnabled(false);
        ui->tab_3->setEnabled(false);
        break;
    case Button:
        ui->tab_2->setEnabled(true);
        ui->tab_3->setEnabled(true);
        break;
    case Text:
        ui->tab_2->setEnabled(true);
        break;
    case Edit:
        ui->tab_2->setEnabled(true);
        ui->tab_3->setEnabled(true);
        break;
    default:
        return;
    }

    initDialog();

    this->setWindowTitle(QString("%1-[%2]").arg(m_title).arg(name));
    this->show();
    this->raise();
}


void PropertyDialog::on_buttonBox_accepted()
{
    m_widget->setTextFont(ui->textFont->currentIndex());
    m_widget->setTextRegAddress(ui->textRegAddress->value());
    m_widget->setTextTotLen(ui->textDotBef->value());
    m_widget->setTextDotLen(ui->textDotAft->value());
    setStringList();

    m_widget->setLuaCmd(ui->LuaEditor->toPlainText());
    m_widget->refresh();
    emit m_widget->currentItemChanged(m_widget);
}

void PropertyDialog::on_textType_currentIndexChanged(int index)
{
    m_widget->setTextType(index);
    switch (index) {
    case String:
        ui->textRegAddress->setEnabled(false);
        ui->textDotBef->setEnabled(false);
        ui->textDotAft->setEnabled(false);
        ui->stackedWidget->setCurrentIndex(0);
        ui->textEdit->setEnabled(true);
        break;
    case RegVaule:
        ui->textRegAddress->setEnabled(true);
        ui->textDotBef->setEnabled(true);
        ui->textDotAft->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(0);
        ui->textEdit->setEnabled(false);
        break;
    case StringList:
        ui->textRegAddress->setEnabled(true);
        ui->textDotBef->setEnabled(false);
        ui->textDotAft->setEnabled(false);
        ui->stackedWidget->setCurrentIndex(1);
        break;
    default:
        break;
    }
}

void PropertyDialog::on_textListAdd_clicked()
{
    int curIdx = ui->textList->currentRow()+1;
    QTableWidgetItem *item;
    ui->textList->insertRow(curIdx);
    for(int i=0;i<LAN_NUM;i++){
        item = new QTableWidgetItem();
       ui->textList->setItem(curIdx, i, item);
    }
    ui->textList->setCurrentCell(curIdx, 0);
}

void PropertyDialog::on_textListRemove_clicked()
{
    int curIdx = ui->textList->currentRow();
    if (curIdx >= 0){
        ui->textList->removeRow(curIdx);
    }
}

void PropertyDialog::on_textUp_clicked()
{
    int curIdx = ui->textList->currentRow();
    if (curIdx > 0){
        QTableWidgetItem *item1 = ui->textList->takeItem(curIdx-1, 0);
        QTableWidgetItem *item2 = ui->textList->takeItem(curIdx, 0);

        ui->textList->setItem(curIdx-1, 0, item2);
        ui->textList->setItem(curIdx, 0, item1);
    }
}

void PropertyDialog::on_textDown_clicked()
{
    int curIdx = ui->textList->currentRow();
    if ((curIdx >= 0) && (curIdx < (ui->textList->rowCount()-1))){
        QTableWidgetItem *item1 = ui->textList->takeItem(curIdx, 0);
        QTableWidgetItem *item2 = ui->textList->takeItem(curIdx+1, 0);

        ui->textList->setItem(curIdx, 0, item2);
        ui->textList->setItem(curIdx+1, 0, item1);
    }
}

void PropertyDialog::on_textColor_clicked()
{
    QColor color = QColorDialog::getColor(m_widget->getTextColor(), this);

    ui->textColor->setStyleSheet(QString("background-color: #%1;")
                                .arg(QString::number(color.rgba(), 16)));
    m_widget->setTextColor(color);
}

void PropertyDialog::on_textAlignH_currentIndexChanged(int index)
{
    m_widget->setAlignH(index);
}


void PropertyDialog::on_textAlignV_currentIndexChanged(int index)
{
    m_widget->setAlignV(index);
}

void PropertyDialog::on_textEdit_textChanged()
{
    m_widget->setTextString(ui->textEdit->toPlainText());
    m_widget->setTextMaxLen(128);
}

void PropertyDialog::initDialog()
{
    ui->baseId->setValue(m_widget->getId());
    ui->baseBkColor->setStyleSheet(QString("background-color: #%1;")
                                   .arg(QString::number(m_widget->getBkColor().rgba(), 16)));

    ui->textColor->setStyleSheet(QString("background-color: #%1;")
                                .arg(QString::number(m_widget->getTextColor().rgba(), 16)));

    ui->textType->setCurrentIndex(m_widget->getTextType());
    ui->textRegAddress->setValue(m_widget->getTextRegAddress());
    ui->textDotBef->setValue(m_widget->getTextTotLen());
    ui->textDotAft->setValue(m_widget->getTextDotLen());

    on_textType_currentIndexChanged(m_widget->getTextType());
    on_textAlignH_currentIndexChanged(m_widget->getAlignH());
    on_textAlignV_currentIndexChanged(m_widget->getAlignV());

    ui->textEdit->setText(m_widget->getTextString());
    ui->textList->clear();
    ui->textList->setRowCount(0);
    getStringList();


    ui->LuaEditor->setText(m_widget->getLuaCmd());
}

void PropertyDialog::getStringList()
{
    for(int j=0;j<LAN_NUM;j++){
        QStringList strList = m_widget->getLanStringList(j);
        for(int i=0;i<strList.count();i++){
            if (j==0)
                on_textListAdd_clicked();
            ui->textList->item(i, j)->setText(strList[i]);
        }
    }
}

void PropertyDialog::setStringList()
{

    QString str;
    int maxLen = 0;
    if (ui->textType->currentIndex() == StringList){
        for (int k=0;k<LAN_NUM;k++){
            QStringList strList;
            for(int i=0;i<ui->textList->rowCount();i++){
                str = ui->textList->item(i, k)->text();
                strList.append(str);
                if (str.count() > maxLen){
                    maxLen = str.count();
                }
            }
            m_widget->setLanStringList(k, strList);
        }
        m_widget->setTextMaxLen(maxLen+1);  //这里+1是要加入结束符
    }
}


void PropertyDialog::on_textFont_currentIndexChanged(int index)
{
    m_widget->setTextFont(index);
}

void PropertyDialog::on_baseId_valueChanged(int arg1)
{
    m_widget->setId(arg1);
}

void PropertyDialog::on_baseBkColor_clicked()
{
    QColor color = QColorDialog::getColor(m_widget->getBkColor(), this);

    ui->baseBkColor->setStyleSheet(QString("background-color: #%1;")
                                .arg(QString::number(color.rgba(), 16)));
    m_widget->setBkColor(color);
}
