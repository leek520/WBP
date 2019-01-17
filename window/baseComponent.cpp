#include "baseComponent.h"

ComboBox::ComboBox(QWidget *parent) :
    QComboBox(parent)
{

}

void ComboBox::setVaule(int index)
{
    if (index < PV->getEnumProperty("InternalReg").count()){
        setCurrentIndex(index);
    }else{
        setCurrentText(QString::number(index));
    }
}

int ComboBox::value()
{
    return currentIndex();
}
