#include "TdPreCompile.h" //QApplication

#include "CommonHeader.h" //

#include "ApplicationNameManager.h" //ApplicationNameManager

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
    
  QTranslator CnTrns;
  CnTrns.load("PublicServer"); //载入翻译文件。

  a.installTranslator(&CnTrns); //安装翻译文件。
  ApplicationNameManager *applicationNameManager =new ApplicationNameManager ; //Application name manager.
  Q_UNUSED(applicationNameManager)

  a.addLibraryPath(a.applicationDirPath ()); //添加插件目录。

  MainLogic mainLogic; //主逻辑。

  return a.exec();
}
