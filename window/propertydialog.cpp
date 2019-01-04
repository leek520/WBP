#include "propertydialog.h"
#include "ui_propertydialog.h"

PropertyDialog::PropertyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertyDialog)
{
    ui->setupUi(this);
    m_title = this->windowTitle();
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
    this->setModal(true);
    this->show();
}


void PropertyDialog::on_buttonBox_accepted()
{
    m_widget->setTextRegAddress(ui->textRegAddress->value());
    m_widget->setTextDotBef(ui->textDotBef->value());
    m_widget->setTextDotAft(ui->textDotAft->value());
    setStringList();

    m_widget->setLuaCmd(ui->LuaEditor->toPlainText());
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
    QTableWidgetItem *item = new QTableWidgetItem();
    ui->textList->insertRow(curIdx);
    ui->textList->setItem(curIdx, 0, item);
    ui->textList->setCurrentItem(item);
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
    QColor color = QColorDialog::getColor(m_widget->getBkColor(), this);

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
    ui->textColor->setStyleSheet(QString("background-color: #%1;")
                                .arg(QString::number(m_widget->getBkColor().rgba(), 16)));

    ui->textType->setCurrentIndex(m_widget->getTextType());
    ui->textRegAddress->setValue(m_widget->getTextRegAddress());
    ui->textDotBef->setValue(m_widget->getTextDotBef());
    ui->textDotAft->setValue(m_widget->getTextDotAft());

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
    QStringList strList = m_widget->getTextStringList();
    for(int i=0;i<strList.count();i++){
        on_textListAdd_clicked();
        ui->textList->item(i, 0)->setText(strList[i]);
    }
}

void PropertyDialog::setStringList()
{
    QStringList strList;
    QString str;
    int maxLen = 0;
    if (ui->textType->currentIndex() == StringList){
        for(int i=0;i<ui->textList->rowCount();i++){
            str = ui->textList->item(i, 0)->text();
            strList.append(str);
            if (str.count() > maxLen){
                maxLen = str.count();
            }
        }
        m_widget->setTextMaxLen(maxLen);
        m_widget->setTextStringList(strList);
    }
}
