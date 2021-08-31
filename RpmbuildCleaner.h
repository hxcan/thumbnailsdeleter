#ifndef RPMBUILDCLEANER_H
#define RPMBUILDCLEANER_H

#include "TdPreCompile.h" //QTcpServer

#include "RangeSortSearch.h" //RangeSortSearch

#include "ui_TrashCleaner.h" //TrashCleaner
#include "ui_RpmbuildCleaner.h" //RpmbuildCleaner

namespace Ui {
class RpmbuildCleaner;
}

class RpmbuildCleaner : public QMainWindow
{
    Q_OBJECT
public:
    explicit RpmbuildCleaner(QWidget *parent = 0);

private slots:
    void Delete1File(); //!<Delete timer timed out,then delete 1 file.

private:
    QTimer DltTimer; //!<Delte timer.

    QQueue<QString> oldThumbnailFiles; //!<旧的缩略图文件。
    void startDelete(); //!<搜索完毕，则开始删除。
    RangeSortSearch<QString> rangeSortSearch; //!<范围排序搜索器。
    QFutureWatcher<QStringList> subDirsFutureWatcher; //!<用于监听列出子目录过程的未来观察器。
    QList<QString> scanningDirList; //!<当前正在扫描的目录的列表。
    QQueue<QString> DirsQueue; //!<The directories queue.
    void startWork(); //!<开始工作。
    void connectSignals(); //!<连接信号槽。
    void initializeMembers(); //!<初始化成员变量。
    void scanSubDir(QList<QString> scanningDirList2Scan); //!<扫描子目录。
    QTimer startWorkTimer; //!<触发开始工作动作的定时器。
    Ui::RpmbuildCleaner *ui; //!<用户界面。
    QString ThumbnailsDirName; //!<配置文件的目录名。
    void scanDirsNextLevel(); //!<扫描下一个层次的子目录。
    void listDirFiles(); //!<开始列出各个子目录下的文件。
    QFutureWatcher<QStringList> fileListFutureWatcher; //!<用于监听列出目录下的文件的过程的未来观察器。
    void startRecognizeFile(); //!<开始识别一个个的文件。
    QQueue<QString> FilesQueue; //!<The file paths queue.
    
signals:
    void finished(); //!<信号，已经完成。

};

#endif //
