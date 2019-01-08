#ifndef COMPLETER_H
#define COMPLETER_H
#include <QApplication>
#include <QFile>
#include <QCompleter>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QAbstractItemView>
class Completer : public QCompleter
{
    Q_OBJECT
public:
    explicit Completer(QObject *parent = 0);

private:
    QAbstractItemModel *modelFromFile(const QString& fileName);
public slots:
};

#endif // COMPLETER_H
