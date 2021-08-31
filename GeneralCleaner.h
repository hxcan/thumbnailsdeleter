#ifndef GENERALCLEANER_H
#define GENERALCLEANER_H

#include "TdPreCompile.h" //QTcpServer

#include "RangeSortSearch.h" //RangeSortSearch

#include "ui_GeneralCleaner.h" //TrashCleaner

namespace Ui {
class GeneralCleaner;
}

class GeneralCleaner : public QMainWindow
{
    Q_OBJECT
public:
    explicit GeneralCleaner( const QString directoryName ,QWidget *parent = 0); //!<构造函数。

private slots:
    void Delete1File(); //!<Delete timer timed out,then delete 1 file.

private:
    void deleteBrokenFileByInode(quint64 inode); //!<利用索引编号删除这个破损文件。
    QString currentBrokenFileDirPath; //!<当前正在处理的损坏文件名文件的目录路径。
    void reportTunnelFinish(int extCd); //!<隧道进程结束，则报告状态。
    QString SshCmd="ls"; //!<ssh命令。
    QString FindCmd="find"; //!<find命令。
    QProcess CrtPrc; //!<用来运行SSH隧道的进程。
    void lsDirWithInodeNumber(QString fileDirPath); //!<列出该目录下的文件列表，带索引编号。
    void delete1BrokenFileName(); //!<删除一个具有破损文件名的文件。
    void startDeleteBrokenFileName(); //!<开始删除具有破损文件名的文件。
    QQueue<QString> brokenFileNameQueue; //!<破损文件名列表。
    void updateListFileProgress(int progressValue); //!<列出文件的进度发生变化，则更新进度值。
    qint32 MaxSubDirScanTime=10*10000; //!<扫描子目录的最长时间。毫秒。
    QTime subDirScanTime; //!<扫描子目录的计时器。
    int scanSubDirPass=0; //!<扫描子代目录的遍数。
    QTimer DltTimer; //!<Delte timer.
    void updateSearchProgress(quint64 progressValue); //!<搜索进度发生变化，则更新搜索进度。
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
    Ui::GeneralCleaner *ui; //!<用户界面。
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
