#ifndef PROPERTYDIALOG_H
#define PROPERTYDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include "widget.h"
#include "publicvar.h"
namespace Ui {
class PropertyDialog;
}

class PropertyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertyDialog(QWidget *parent = 0);
    ~PropertyDialog();
    void showDialog(Widget *w);
private slots:
    void on_buttonBox_accepted();

    void on_textType_currentIndexChanged(int index);

    void on_textListAdd_clicked();

    void on_textListRemove_clicked();

    void on_textUp_clicked();

    void on_textDown_clicked();

    void on_textColor_clicked();

    void on_textAlignH_currentIndexChanged(int index);

    void on_textAlignV_currentIndexChanged(int index);

    void on_textEdit_textChanged();


    void on_textFont_currentIndexChanged(int index);

    void on_baseId_valueChanged(int arg1);

    void on_baseBkColor_clicked();

    void on_imagePath_clicked();

    void on_imageCompress_currentIndexChanged(int index);

    void on_writeRegType_currentIndexChanged(int index);

private:
    void setProperty();
    void getProperty();
    void getStringList();
    void setStringList();
private:
    Ui::PropertyDialog *ui;
    Widget *m_widget;
    QString m_title;
};

#endif // PROPERTYDIALOG_H
