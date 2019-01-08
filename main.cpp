#include "./window/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置程序中文字的编码方式
    QTextCodec *codec = QTextCodec::codecForName("UTF_8");
    QTextCodec::setCodecForLocale(codec);

    //设置字体
    QFont font;
    //font.setFamily(QObject::tr("宋体"));
    font.setPixelSize(12);
    a.setFont(font);

    // 加载QSS样式
    CommonHelper::setStyle(":/win_style");


    MainWindow w;
    w.show();

    return a.exec();
}


