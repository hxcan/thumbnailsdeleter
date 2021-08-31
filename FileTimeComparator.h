#ifndef FILETIMECOMPARATOR_H
#define FILETIMECOMPARATOR_H

#include "TdPreCompile.h" //QTcpServer

#include "RangeSortSearch.h" //RangeSortSearch

#include "MainLogic.h" //DictItem

namespace Ui {
class ThumbnailsDeleter;
}

class FileTimeComparator : public PaComparator<QString>
{
public:
    int getDifference(QString dir2Scan, QString compareBase) override
    {
        QFileInfo currentFile(dir2Scan);
        QFileInfo baseFile(compareBase);

        qint64 currentFileLastModifiedMsecs=currentFile.lastModified ().toMSecsSinceEpoch() ;
        qint64 baseFileLastModifiedMsecs=baseFile.lastModified ().toMSecsSinceEpoch();
        
        int result=(currentFileLastModifiedMsecs - baseFileLastModifiedMsecs);
        
        return result;
    } //int getDifference(QString dir2Scan, QString compareBase) override
    
    CompareResultRelation paCompare (QString currentElement, QString baseElement) override
    {
        QFileInfo currentFile(currentElement);
        QFileInfo baseFile(baseElement);

        CompareResultRelation result;
        
        qint64 currentFileLastModifiedMsecs=currentFile.lastModified ().toMSecsSinceEpoch() ;
        qint64 baseFileLastModifiedMsecs=baseFile.lastModified ().toMSecsSinceEpoch();
        

        if (currentFileLastModifiedMsecs < baseFileLastModifiedMsecs)
        {
            result=LessThan;
        } //if (currentElement<baseElement)
        else if (currentFileLastModifiedMsecs==baseFileLastModifiedMsecs)
        {
            result=Equal;
        } //else if (currentElement==baseElement)
        else
        {
            result=GreaterThan;
        } //else

        return result;
    } //CompareResultRelation paCompare (QString currentElement, QString baseElement)

private:
    RangeSortSearch<QString> rangeSortSearch; //!<范围排序搜索器。
    QFutureWatcher<QStringList> subDirsFutureWatcher; //!<用于监听列出子目录过程的未来观察器。
    QList<QString> scanningDirList; //!<当前正在扫描的目录的列表。
    QQueue<QString> DirsQueue; //!<The directories queue.
    void initializeMembers(); //!<初始化成员变量。
    QTimer startWorkTimer; //!<触发开始工作动作的定时器。
    Ui::ThumbnailsDeleter *ui; //!<用户界面。
    void listDirFiles(); //!<开始列出各个子目录下的文件。
    QFutureWatcher<QStringList> fileListFutureWatcher; //!<用于监听列出目录下的文件的过程的未来观察器。
    QQueue<QString> FilesQueue; //!<The file paths queue.

};

#endif //
