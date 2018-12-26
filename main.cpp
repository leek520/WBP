#include "./window/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置程序中文字的编码方式
    QTextCodec *codec = QTextCodec::codecForName("UTF_8");
    QTextCodec::setCodecForLocale(codec);


    MainWindow w;
    w.show();

    return a.exec();
}


