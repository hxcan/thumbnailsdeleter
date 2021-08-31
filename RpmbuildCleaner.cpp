#include "TdPreCompile.h" //QFile


#include "ThumbnailsDeleter.h"
#include "CommonHeader.h" //DataType
#include "ui_ThumbnailsDeleter.h"
#include "mapReduceFunctions.h" //getSubDirs
#include "FileTimeComparator.h" //FileTimeComparator
#include "TrashCleaner.h" //TrashCleaner
#include "RpmbuildCleaner.h" //RpmbuildCleaner

/*!
 * \brief ThumbnailsDeleter::initializeMembers 初始化成员变量。
 */
void RpmbuildCleaner::initializeMembers()
{
    startWorkTimer.setInterval (30); //30ms轮询一次。
    startWorkTimer.setSingleShot (true); //单发。

    ThumbnailsDirName=QDir::homePath ()+"/rpmbuild/"; //缩略图目录名。
} //void ThumbnailsDeleter::initializeMembers()

/*!
 * \brief FakeImageEliminator::listDirFiles 开始列出各个子目录下的文件。
 */
void RpmbuildCleaner::listDirFiles()
{
    QFuture<QStringList> fileList=QtConcurrent::mappedReduced(DirsQueue,getSubDirFileList,addToFileList); //启动一个并行映射归并过程。
    fileListFutureWatcher.setFuture(fileList); //设置未来对象。
} //void FakeImageEliminator::listDirFiles()


/*!
 * \brief FakeImageEliminator::startRecognizeFile 开始识别一个个的文件。
 */
void RpmbuildCleaner::startRecognizeFile()
{
    qDebug() << __FILE__ << __LINE__ << __func__ << tr("File listing finished."); //Debug.
    qDebug() << __FILE__ << __LINE__ << __func__ << tr("Start recognizing files.Time:") << QTime::currentTime ().toString (); //Debug.

    QFuture<QStringList> subDirFutr=fileListFutureWatcher.future (); //获取未来对象。

    QStringList subDirs=subDirFutr.result(); //获取扫描到的结果。

    FilesQueue.append(subDirs); //将当前扫描到的文件列表追加到整个要扫描的文件列表中。

    DirsQueue.clear (); //清空当前正在扫描的目录列表。

    FileTimeComparator * fileTimeComparator=new FileTimeComparator(); //创建比较器。

    int targetAmount=FilesQueue.size ()*30/100; //目标个数。
    
    if (FilesQueue.size()==0) //没有任何文件。
    {
        emit finished(); //发射信号，已经完成。
        
        statusBar()->showMessage(tr("Finished.")); //显示状态。
        
    } //if (FilesQueue.size()==0) //没有任何文件。
    else //有文件。
    {
        rangeSortSearch.startSearch(FilesQueue,fileTimeComparator,targetAmount); //开始排序并寻找指定个数的元素。
        
    } //else //有文件。

} //void FakeImageEliminator::startRecognizeFile()

/*!
 * \brief ThumbnailsDeleter::startWork 开始工作。
 */
void RpmbuildCleaner::startWork()
{
    QListWidgetItem * CrtFlItm=new QListWidgetItem(ThumbnailsDirName); //Current file path item.


    ui->imageFileUserlistWidget->addItem(CrtFlItm); //Add to the file item list.
    ui->DrAmtlabel_2->setText(tr("%1").arg(ui->imageFileUserlistWidget->count())); //Set the amount.

    DirsQueue.enqueue(ThumbnailsDirName); //Add the target directory into the directories queue.

    scanningDirList.append(ThumbnailsDirName); //加入到当前正在扫描的目录列表中。

    scanSubDir(scanningDirList); //扫描子目录。
} //void ThumbnailsDeleter::startWork()

/*!
 * \brief FakeImageEliminator::Delete1File Delete timer timed out,then delete 1 file.
 */
void RpmbuildCleaner::Delete1File()
{
    if (oldThumbnailFiles.isEmpty()) //The queue is empty.
    {
        DltTimer.stop(); //Stop the timer.

        emit finished(); //发射信号，已经完成。
        
        statusBar()->showMessage(tr("Finished.")); //显示状态。
    } //if (NonImgQueue.isEmpty()) //The queue is empty.
    else //The queue is not empty.
    {
        QString CrtFlNm=oldThumbnailFiles.dequeue(); //Get the current file name.

        QFile CrtFl(CrtFlNm); //Create the file object.

        CrtFl.remove(); //Remove the file.
        
        statusBar()->showMessage(tr("Deleting %1").arg(CrtFlNm)); //显示状态。
        
    } //else //The queue is not empty.
} //void FakeImageEliminator::Delete1File() //!<Delete timer timed out,then delete 1 file.

/*!
 * \brief ThumbnailsDeleter::connectSignals 连接信号槽。
 */
void RpmbuildCleaner::connectSignals()
{
    connect (&startWorkTimer,&QTimer::timeout,this,&RpmbuildCleaner::startWork); //定时器超时，则开始工作。
    connect(&subDirsFutureWatcher,&QFutureWatcher<QStringList>::finished,this,&RpmbuildCleaner::scanDirsNextLevel); //扫描下一个层次的子目录。
    connect(&fileListFutureWatcher,&QFutureWatcher<QStringList>::finished,this,&RpmbuildCleaner::startRecognizeFile); //开始识别一个个的文件。
    connect (rangeSortSearch.getSignalProxy (),&PaSignalProxy::finished,this,&RpmbuildCleaner::startDelete); //搜索完毕，则开始删除。

    connect(&DltTimer,SIGNAL(timeout()),this,SLOT(Delete1File())); //Delete timer timed out,then delete 1 file.

} //void ThumbnailsDeleter::connectSignals()

/*!
 * \brief ThumbnailsDeleter::startDelete 搜索完毕，则开始删除。
 */
void RpmbuildCleaner::startDelete()
{
    QStringList oldFiles=rangeSortSearch.getResult (); //获取结果。

    oldThumbnailFiles.append(oldFiles);

    DltTimer.start(); //Start the delete timer.
} //void ThumbnailsDeleter::startDelete()

/*!
 * \brief FakeImageEliminator::scanDirsNextLevel 扫描下一个层次的子目录。
 */
void RpmbuildCleaner::scanDirsNextLevel()
{
    QFuture<QStringList> subDirFutr=subDirsFutureWatcher.future (); //获取未来对象。

    QStringList subDirs=subDirFutr.result(); //获取扫描到的结果。

    if (subDirs.size ()) //有新结果。
    {
        DirsQueue.append(subDirs); //将当前扫描到的子目录列表追加到整个要扫描的目录列表中。

        scanningDirList.clear (); //清空当前正在扫描的目录列表。
        scanningDirList.append(subDirs); //加入到当前正在扫描的目录列表中。

        scanSubDir(scanningDirList); //扫描子目录。
    } //if (subDirs.size ()) //有新结果。
    else //没有新结果，则应当进行下一步骤的扫描了。扫描各个目录中的文件。
    {
        listDirFiles(); //开始列出各个子目录下的文件。
    } //else //没有新结果，则应当进行下一步骤的扫描了。扫描各个目录中的文件。
} //void FakeImageEliminator::scanDirsNextLevel()

RpmbuildCleaner::RpmbuildCleaner(QWidget *parent) : QMainWindow(parent), ui(new Ui::RpmbuildCleaner)
{
    ui->setupUi (this); //初始化用户界面。

    initializeMembers(); //初始化成员变量。

    startWorkTimer.start(); //启动enet轮询定时器。

    connectSignals(); //连接信号槽。
}

/*!
 * \brief FakeImageEliminator::scanSubDir 扫描子目录。
 * \param scanningDirList2Scan 要扫描其子目录的目录名列表。
 */
void RpmbuildCleaner::scanSubDir(QList<QString> scanningDirList2Scan)
{
    QFuture<QStringList> subDirs=QtConcurrent::mappedReduced(scanningDirList2Scan,getSubDirs,addToSubDirList); //启动一个并行映射归并过程。
    subDirsFutureWatcher.setFuture(subDirs); //设置未来对象。
} //void FakeImageEliminator::scanSubDir(QList<QString> scanningDirList2Scan)
