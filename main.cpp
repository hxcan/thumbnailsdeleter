#include "TdPreCompile.h" //QApplication

#include "CommonHeader.h" //

#include "TrashCleaner.h" //TrashCleaner

#include "RpmbuildCleaner.h" //RpmbuildCleaner

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QTranslator CnTrns;
    CnTrns.load("PublicServer"); //载入翻译文件。

    a.installTranslator(&CnTrns); //安装翻译文件。

    a.addLibraryPath(a.applicationDirPath ()); //添加插件目录。

    MainLogic mainLogic; //主逻辑。
    

    return a.exec();
}
