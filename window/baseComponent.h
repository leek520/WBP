#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include "publicvar.h"
class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = 0);
    void setVaule(int index);
    int value();
signals:

public slots:
};

#endif // COMBOBOX_H
