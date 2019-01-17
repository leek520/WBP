import os
import shutil



def SearchFile(path, targetDir, text):
    try:
        files=os.listdir(path)

        for f in files:
            fl= os.path.join(path,f)
            if os.path.isdir(fl):
                SearchFile(fl, targetDir, text) 
            elif os.path.isfile(fl) and os.path.splitext(fl)[1]==text:	# os.path.splitext():分离文件名与扩展名
                #print(fl) 
                shutil.copy(fl,  targetDir)
    except Exception:
        print(u'文件查询失败.')

def CopyOtherFile(files, targetDir):
    for file in files:
        shutil.copy(file,  targetDir)
   
if __name__ == '__main__':
    app_name = 'Qwbp.exe'
    sourceDir = r'D:\2-Work\leek.project\WBP\output\Release\release'
    targetDir = r'D:\2-Work\leek.project\WBP\output\bin'
    otherDllFile = [r'C:\Qt\Qt5.6.2\5.6\mingw49_32\bin\Qt5SerialPort.dll']
   
      
    #查找并拷贝dll
    #SearchFile(sourceDir, targetDir, '.dll')
    #查找并拷贝exe:#重命名可执行文件
    SearchFile(sourceDir, os.path.join(targetDir, app_name), '.exe')
    
    #额外需要拷贝的文件，这里是串口类和其他文件
    CopyOtherFile(otherDllFile, targetDir)
    
    #执行cmd命令，用QT自带打包工具打包dll	
    #注意这里windows下，后面路径要加引号
    cmd = r"C:\Qt\Qt5.6.2\5.6\mingw49_32\bin\qtenv2.bat && windeployqt "  + targetDir + "\\" + app_name 
    os.system(cmd)




