#include "bmp2array.h"

Bmp2Array::Bmp2Array(QObject *parent) : QObject(parent)
{

}

/*
 * 转565无压缩
BmpCvt.exe 1.bmp  -saveaslogo,1,8 -exit

 * 转565压缩
BmpCvt.exe 1.bmp  -saveaslogo,1,12 -exit
*/
