#include "TdPreCompile.h" //QFile


#include "ThumbnailsDeleter.h"
#include "CommonHeader.h" //DataType
#include "ui_ThumbnailsDeleter.h"
#include "mapReduceFunctions.h" //getSubDirs
#include "FileTimeComparator.h" //FileTimeComparator

/*!
 * \brief ThumbnailsDeleter::initializeMembers 初始化成员变量。
 */
void FileTimeComparator::initializeMembers()
{
    startWorkTimer.setInterval (30); //30ms轮询一次。
    startWorkTimer.setSingleShot (true); //单发。
} //void ThumbnailsDeleter::initializeMembers()

/*!
 * \brief FakeImageEliminator::listDirFiles 开始列出各个子目录下的文件。
 */
void FileTimeComparator::listDirFiles()
{
    QFuture<QStringList> fileList=QtConcurrent::mappedReduced(DirsQueue,getSubDirFileList,addToFileList); //启动一个并行映射归并过程。
    fileListFutureWatcher.setFuture(fileList); //设置未来对象。



    return;
} //void FakeImageEliminator::listDirFiles()
