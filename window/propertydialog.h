#ifndef PROPERTYDIALOG_H
#define PROPERTYDIALOG_H

#include <QDialog>

namespace Ui {
class PropertyDialog;
}

class PropertyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertyDialog(QWidget *parent = 0);
    ~PropertyDialog();

private:
    Ui::PropertyDialog *ui;
};

#endif // PROPERTYDIALOG_H
