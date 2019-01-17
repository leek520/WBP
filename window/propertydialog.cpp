#include "propertydialog.h"
#include "ui_propertydialog.h"

PropertyDialog::PropertyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertyDialog),
    m_widget(NULL)
{
    ui->setupUi(this);
    m_title = this->windowTitle();

    //设置表头
    ui->textList->horizontalHeader()->setVisible(true);
    ui->textList->setColumnCount(LAN_NUM);

    ui->imageCompress->addItems(PV->getEnumProperty("ImageCompress"));
    ui->textType->addItems(PV->getEnumProperty("TextType"));
    ui->textAlignH->addItems(PV->getEnumProperty("AlignH"));
    ui->textAlignV->addItems(PV->getEnumProperty("AlignV"));
    ui->textFont->addItems(PV->getEnumProperty("TextFont"));
    ui->textRegType->addItems(PV->getEnumProperty("RegType"));

    ui->writeRegInternal->addItems(PV->getEnumProperty("InternalReg"));
    ui->writeRegType->addItems(PV->getEnumProperty("WriteRegType"));
    ui->writeValueType->addItems(PV->getEnumProperty("WriteValueType"));
    ui->writeRegAddress->setRange(InterRegEnd, VAR_BUF_LEN);

    ui->keyBoard->addItems(PV->getEnumProperty("KeyBoard"));
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
        ui->baseStack->setCurrentIndex(0);

        ui->tabwidget->removeTab(3);
        ui->tabwidget->removeTab(2);
        ui->tabwidget->removeTab(1);

        ui->baseId->setEnabled(true);
        ui->boxPage->setVisible(true);
        break;
    case Button:
        ui->baseStack->setCurrentIndex(0);
        ui->tabwidget->addTab(ui->tabText, "文本属性");
        ui->tabwidget->addTab(ui->tabSecurity, "安全属性");
        ui->tabwidget->addTab(ui->tabAction, "动作属性");

        ui->baseId->setEnabled(false);
        ui->boxPage->setVisible(false);
        break;
    case Text:
        ui->baseStack->setCurrentIndex(0);

        ui->tabwidget->addTab(ui->tabText, "文本属性");
        ui->tabwidget->addTab(ui->tabSecurity, "安全属性");
        ui->tabwidget->removeTab(3);

        ui->baseId->setEnabled(false);
        ui->boxPage->setVisible(false);
        break;
    case Edit:
        ui->baseStack->setCurrentIndex(0);

        ui->tabwidget->addTab(ui->tabText, "文本属性");
        ui->tabwidget->addTab(ui->tabSecurity, "安全属性");
        ui->tabwidget->removeTab(3);

        ui->baseId->setEnabled(false);
        ui->boxPage->setVisible(false);
        break;
    case Image:
        ui->tabwidget->removeTab(3);
        ui->tabwidget->removeTab(2);
        ui->tabwidget->removeTab(1);
        ui->baseStack->setCurrentIndex(1);
        break;
    case Line:
    case Rect:
    case Circle:
        ui->tabwidget->removeTab(3);
        ui->tabwidget->removeTab(2);
        ui->tabwidget->removeTab(1);
        ui->baseStack->setCurrentIndex(2);
        break;
    default:
        return;
    }

    getProperty();

    this->setWindowTitle(QString("%1-[%2]").arg(m_title).arg(name));
    this->show();
    this->raise();
}

void PropertyDialog::on_buttonBox_accepted()
{
    setProperty();
}

void PropertyDialog::on_textType_currentIndexChanged(int index)
{
    if (!m_widget) return;
    m_widget->setTextType(index);
    switch (index) {
    case String:
        ui->textRegAddress->setEnabled(false);
        ui->textDotBef->setEnabled(false);
        ui->textDotAft->setEnabled(false);
        ui->textStack->setCurrentIndex(0);
        ui->textEdit->setEnabled(true);

        break;
    case RegVaule:
        ui->textRegAddress->setEnabled(true);
        ui->textDotBef->setEnabled(true);
        ui->textDotAft->setEnabled(true);
        ui->textStack->setCurrentIndex(0);
        ui->textEdit->setEnabled(false);
        break;
    case StringList:
        ui->textRegAddress->setEnabled(true);
        ui->textDotBef->setEnabled(false);
        ui->textDotAft->setEnabled(false);
        ui->textStack->setCurrentIndex(1);
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
    if (!m_widget) return;
    m_widget->setAlignH(index);
}


void PropertyDialog::on_textAlignV_currentIndexChanged(int index)
{
    if (!m_widget) return;
    m_widget->setAlignV(index);
}

void PropertyDialog::on_textEdit_textChanged()
{
    if (!m_widget) return;
    m_widget->setTextString(ui->textEdit->toPlainText());
    m_widget->setTextMaxLen(128);
}

void PropertyDialog::getProperty()
{
    /*write*/
    ui->actionEnableCk->setChecked(m_widget->getWriteEnable());
    on_actionEnableCk_clicked(m_widget->getWriteEnable());
    int type = m_widget->getWriteRegType();
    ui->writeRegType->setCurrentIndex(type);
    if (type == 0){
        ui->writeRegInternal->setCurrentIndex(m_widget->getWriteRegAddress());
    }else{
        ui->writeRegAddress->setValue(m_widget->getWriteRegAddress());
    }
    ui->writeCheckBit->setChecked(m_widget->getIsBitReg());
    ui->writeBitAddress->setValue(m_widget->getWriteBitAddress());
    on_writeCheckBit_clicked(m_widget->getIsBitReg());

    ui->writeValueType->setCurrentIndex(m_widget->getWriteValueType());
    ui->writeValue->setValue(m_widget->getWriteValue());
    /*image*/
    ui->imageCompress->setCurrentIndex(m_widget->getImageCompress());

    /*base*/
    ui->baseId->setValue(m_widget->getId());
    ui->baseBkColor->setStyleSheet(QString("background-color: #%1;")
                                   .arg(QString::number(m_widget->getBkColor().rgba(), 16)));
    ui->PermanentCk->setChecked(m_widget->getPermanent());
    /*text*/
    ui->textColor->setStyleSheet(QString("background-color: #%1;")
                                .arg(QString::number(m_widget->getTextColor().rgba(), 16)));

    ui->textType->setCurrentIndex(m_widget->getTextType());
    ui->textRegAddress->setValue(m_widget->getTextRegAddress());
    ui->textDotBef->setValue(m_widget->getTextTotLen());
    ui->textDotAft->setValue(m_widget->getTextDotLen());
    ui->textFont->setCurrentIndex(m_widget->getTextFont());
    ui->textEdit->setText(m_widget->getTextString());
    ui->textList->clear();
    ui->textList->setRowCount(0);

    on_textType_currentIndexChanged(m_widget->getTextType());
    on_textAlignH_currentIndexChanged(m_widget->getAlignH());
    on_textAlignV_currentIndexChanged(m_widget->getAlignV());


    getStringList();

}

void PropertyDialog::setProperty()
{
    /*write*/
    m_widget->setWriteEnable(ui->actionEnableCk->isChecked());

    int type = ui->writeRegType->currentIndex();
    m_widget->setWriteRegType(ui->writeRegType->currentIndex());
    if (type == 0){
        m_widget->setWriteRegAddress(ui->writeRegInternal->currentIndex());
    }else{
        m_widget->setWriteRegAddress(ui->writeRegAddress->value());
    }

    m_widget->setWriteBitAddress(ui->writeBitAddress->value());
    m_widget->setWriteRegType(ui->writeRegType->currentIndex());
    m_widget->setIsBitReg(ui->writeCheckBit->isChecked());
    m_widget->setWriteValueType(ui->writeValueType->currentIndex());
    m_widget->setWriteValue(ui->writeValue->value());

    m_widget->setPermanent(ui->PermanentCk->isChecked());
    /*text*/
    m_widget->setTextFont(ui->textFont->currentIndex());
    m_widget->setTextRegAddress(ui->textRegAddress->value());
    m_widget->setTextTotLen(ui->textDotBef->value());
    m_widget->setTextDotLen(ui->textDotAft->value());
    setStringList();


    m_widget->refresh();
    emit m_widget->currentItemChanged(m_widget);
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
    if (!m_widget) return;
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

void PropertyDialog::on_imagePath_clicked()
{
    //弹出打开对话框
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("选择图片文件"),
                                                    "",
                                                    tr("*.bmp;*.png;*.jpg"));
    if(filename.isEmpty()) return;
    m_widget->setBkImage(filename);
}

void PropertyDialog::on_imageCompress_currentIndexChanged(int index)
{
    if (!m_widget) return;
    m_widget->setImageCompress(index);
}

void PropertyDialog::on_writeRegType_currentIndexChanged(int index)
{
    if (index == 0){
        ui->writeStack->setCurrentIndex(1);
        ui->writeRegAddressLab->setText(tr("选择内部寄存器       "));
    }else{
        ui->writeStack->setCurrentIndex(0);
        ui->writeRegAddressLab->setText(tr("寄存器地址 0000-FFFF"));
    }
}

void PropertyDialog::on_writeCheckBit_clicked(bool checked)
{
    if (checked){
        ui->writeBitAddress->setEnabled(true);
        ui->writeValue->setRange(0,1);
    }else{
        ui->writeBitAddress->setEnabled(false);
        ui->writeValue->setRange(0,65535);
    }

}


void PropertyDialog::on_readAllBtn_clicked()
{
    if (ui->readAllBtn->text() == "全部取消"){
        ui->readAllBtn->setText(tr("全部勾选"));
        ui->readCk1->setChecked(false);
        ui->readCk2->setChecked(false);
        ui->readCk3->setChecked(false);
        ui->readCk4->setChecked(false);
        ui->readCk5->setChecked(false);
        ui->readCk6->setChecked(false);
        ui->readCk7->setChecked(false);
        ui->readCk8->setChecked(false);
        ui->readCk9->setChecked(false);
    }else{
        ui->readAllBtn->setText(tr("全部取消"));
        ui->readCk1->setChecked(true);
        ui->readCk2->setChecked(true);
        ui->readCk3->setChecked(true);
        ui->readCk4->setChecked(true);
        ui->readCk5->setChecked(true);
        ui->readCk6->setChecked(true);
        ui->readCk7->setChecked(true);
        ui->readCk8->setChecked(true);
        ui->readCk9->setChecked(true);
    }
}

void PropertyDialog::on_writeAllBtn_clicked()
{
    if (ui->writeAllBtn->text() == "全部取消"){
        ui->writeAllBtn->setText(tr("全部勾选"));
        ui->writeCk1->setChecked(false);
        ui->writeCk2->setChecked(false);
        ui->writeCk3->setChecked(false);
        ui->writeCk4->setChecked(false);
        ui->writeCk5->setChecked(false);
        ui->writeCk6->setChecked(false);
        ui->writeCk7->setChecked(false);
        ui->writeCk8->setChecked(false);
        ui->writeCk9->setChecked(false);
    }else{
        ui->writeAllBtn->setText(tr("全部取消"));
        ui->writeCk1->setChecked(true);
        ui->writeCk2->setChecked(true);
        ui->writeCk3->setChecked(true);
        ui->writeCk4->setChecked(true);
        ui->writeCk5->setChecked(true);
        ui->writeCk6->setChecked(true);
        ui->writeCk7->setChecked(true);
        ui->writeCk8->setChecked(true);
        ui->writeCk9->setChecked(true);
    }
}


void PropertyDialog::on_keyBoardCk_clicked(bool checked)
{
    if (checked){
        ui->keyBoard->setEnabled(true);
        ui->toolBox->setEnabled(true);
    }else{
        ui->keyBoard->setEnabled(false);
        ui->toolBox->setEnabled(false);
    }
}


void PropertyDialog::on_actionEnableCk_clicked(bool checked)
{
    if (checked){
        ui->boxWrite->setEnabled(true);
        ui->writeStack->setEnabled(true);
        ui->pageWriteRegAddress->setEnabled(true);
        ui->pageWriteRegInternal->setEnabled(true);
        ui->writeRegAddress->setEnabled(true);
        ui->writeRegInternal->setEnabled(true);
    }else{
        ui->boxWrite->setEnabled(false);
    }
}
