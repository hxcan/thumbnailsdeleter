#include "TdPreCompile.h" //QFile


#include "ThumbnailsDeleter.h"
#include "CommonHeader.h" //DataType
#include "ui_ThumbnailsDeleter.h"
#include "mapReduceFunctions.h" //getSubDirs
#include "FileTimeComparator.h" //FileTimeComparator
#include "TrashCleaner.h" //TrashCleaner
#include "GeneralCleaner.h" //GeneralCleaner

/*!
 * \brief ThumbnailsDeleter::initializeMembers 初始化成员变量。
 */
void GeneralCleaner::initializeMembers()
{
    startWorkTimer.setInterval (30); //30ms轮询一次。
    startWorkTimer.setSingleShot (true); //单发。

//    ThumbnailsDirName=QDir::homePath ()+"/.local/share/Trash/files/"; //缩略图目录名。
} //void ThumbnailsDeleter::initializeMembers()

/*!
 * \brief FakeImageEliminator::listDirFiles 开始列出各个子目录下的文件。
 */
void GeneralCleaner::listDirFiles()
{
    QFuture<QStringList> fileList=QtConcurrent::mappedReduced(DirsQueue, getSubDirFileList, addToFileList); //启动一个并行映射归并过程。
    fileListFutureWatcher.setFuture(fileList); //设置未来对象。

    statusBar ()->showMessage (tr("Listing directories")); //显示工作状态。
} //void FakeImageEliminator::listDirFiles()

/*!
 * \brief TrashCleaner::updateListFileProgress 列出文件的进度发生变化，则更新进度值。
 * \param progressValue 进度值。
 */
void GeneralCleaner::updateListFileProgress(int progressValue)
{
    statusBar ()->showMessage (tr("Listing directories, progress: %1").arg(progressValue)); //显示工作状态。
} //void TrashCleaner::updateListFileProgress(int progressValue)

/*!
 * \brief FakeImageEliminator::startRecognizeFile 开始识别一个个的文件。
 */
void GeneralCleaner::startRecognizeFile()
{
    QFuture<QStringList> subDirFutr=fileListFutureWatcher.future (); //获取未来对象。

    QStringList subDirs=subDirFutr.result(); //获取扫描到的结果。

    FilesQueue.append(subDirs); //将当前扫描到的文件列表追加到整个要扫描的文件列表中。

    DirsQueue.clear (); //清空当前正在扫描的目录列表。

    FileTimeComparator * fileTimeComparator=new FileTimeComparator(); //创建比较器。

    int targetAmount=FilesQueue.size ()*40/100; //目标个数。
    
    cout << __FILE__ << ", " << __LINE__ << ", " << __func__ << ", target amount: " << targetAmount << ", whole amount: " << FilesQueue.size() << endl; //Debug.

    statusBar ()->showMessage (tr("Searching for old files, target amount %1").arg (targetAmount)); //显示工作状态。

    if (FilesQueue.length()) //有文件。
    {
        rangeSortSearch.startSearch(FilesQueue, fileTimeComparator, targetAmount); //开始排序并寻找指定个数的元素。
    
    } //if (FilesQueue.length()) //有文件。
    else //无文件
    {
        emit finished(); //发射信号，已经完成。

    } //else //无文件
} //void FakeImageEliminator::startRecognizeFile()

/*!
 * \brief TrashCleaner::updateSearchProgress 搜索进度发生变化，则更新搜索进度。
 * \param progressValue 进度值。
 */
void GeneralCleaner::updateSearchProgress(quint64 progressValue)
{
    int targetAmount=FilesQueue.size ()*40/100; //目标个数。

    statusBar ()->showMessage (tr("Searching for old files, target amount %1, progress %2").arg (targetAmount).arg (progressValue)); //显示工作状态。
} //void TrashCleaner::updateSearchProgress(quint64 progressValue)

/*!
 * \brief ThumbnailsDeleter::startWork 开始工作。
 */
void GeneralCleaner::startWork()
{
    QListWidgetItem * CrtFlItm=new QListWidgetItem(ThumbnailsDirName); //Current file path item.


    QFileInfo targetDireInfo(ThumbnailsDirName); //Check target directory

    if (targetDireInfo.exists()) //Exists
    {
        ui->imageFileUserlistWidget->addItem(CrtFlItm); //Add to the file item list.
        ui->DrAmtlabel_2->setText(tr("%1").arg(ui->imageFileUserlistWidget->count())); //Set the amount.

        DirsQueue.enqueue(ThumbnailsDirName); //Add the target directory into the directories queue.

        scanningDirList.append(ThumbnailsDirName); //加入到当前正在扫描的目录列表中。

        scanSubDir(scanningDirList); //扫描子目录。

        subDirScanTime.start(); //开始计时。

    } //if (targetDireInfo.exists()) //Exists
    else //Not exist
    {
        emit finished(); //Report finished. 陈欣
    } //else //Not exist
} //void ThumbnailsDeleter::startWork()

/*!
 * \brief TrashCleaner::delete1BrokenFileName 删除一个具有破损文件名的文件。
 */
void GeneralCleaner::delete1BrokenFileName()
{
    if (brokenFileNameQueue.isEmpty()) //The queue is empty.
    {
//        DltTimer.stop(); //Stop the timer.

        emit finished(); //发射信号，已经完成。

//        statusBar()->showMessage(tr("Finished.")); //显示状态。

//        startDeleteBrokenFileName(); //开始删除具有破损文件名的文件。
    } //if (NonImgQueue.isEmpty()) //The queue is empty.
    else //The queue is not empty.
    {
        QString CrtFlNm=brokenFileNameQueue.dequeue(); //Get the current file name.

        QFileInfo fileInfo(CrtFlNm); //Debug.

        QString fileDirPath=fileInfo.absolutePath (); //获取文件路径。

        currentBrokenFileDirPath=fileDirPath; //记录目录路径。

        lsDirWithInodeNumber(fileDirPath); //列出该目录下的文件列表，带索引编号。

    } //else //The queue is not empty.
} //void TrashCleaner::delete1BrokenFileName()

/*!
 * \brief TrashCleaner::deleteBrokenFileByInode 利用索引编号删除这个破损文件。
 * \param inode 索引编号。
 */
void GeneralCleaner::deleteBrokenFileByInode(quint64 inode)
{
    QStringList Prmtrs; //命令行参数。

    Prmtrs << "-inum" ; //输出索引编号，一行一个文件。
    Prmtrs << QString::number (inode); //索引编号。


    Prmtrs << "-delete"; //动作是删除。

    qDebug() << __FILE__ << __LINE__ << __func__ << tr("parameters:") << Prmtrs; //Debug.

    QProcess * findCrtPrc=new QProcess;

    findCrtPrc->setWorkingDirectory (currentBrokenFileDirPath); //设置工作目录。

    findCrtPrc->start(FindCmd,Prmtrs); //启动进程。

} //void TrashCleaner::deleteBrokenFileByInode(quint64 inode)

/*!
 * \brief TrashCleaner::lsDirWithInodeNumber 列出该目录下的文件列表，带索引编号。
 * \param fileDirPath 要列出其文件的目录。
 */
void GeneralCleaner::lsDirWithInodeNumber(QString fileDirPath)
{
    QStringList Prmtrs; //命令行参数。

    Prmtrs << "-i1" ; //输出索引编号，一行一个文件。

    Prmtrs << fileDirPath;

    qDebug() << __FILE__ << __LINE__ << __func__ << tr("parameters:") << Prmtrs; //Debug.

    CrtPrc.start(SshCmd,Prmtrs); //启动进程。

} //void TrashCleaner::lsDirWithInodeNumber(QString fileDirPath)

/*!
 * \brief FakeImageEliminator::Delete1File Delete timer timed out,then delete 1 file.
 */
void GeneralCleaner::Delete1File()
{
    if (oldThumbnailFiles.isEmpty()) //The queue is empty.
    {
        DltTimer.stop(); //Stop the timer.

//        emit finished(); //发射信号，已经完成。
        
        statusBar()->showMessage(tr("Finished.")); //显示状态。

        startDeleteBrokenFileName(); //开始删除具有破损文件名的文件。
    } //if (NonImgQueue.isEmpty()) //The queue is empty.
    else //The queue is not empty.
    {
        QString CrtFlNm=oldThumbnailFiles.dequeue(); //Get the current file name.

        QFile CrtFl(CrtFlNm); //Create the file object.

        ui->currentFilelabel->setText (CrtFlNm); //显示当前正在删除的文件名。

        bool  removeResult=CrtFl.remove(); //Remove the file.

        QFileInfo fileInfo(CrtFlNm); //Debug.

        if (removeResult==false) //删除失败。
        {
            if (fileInfo.exists ()==false) //不存在。在这两个条件下，认为是遇到破损文件名了。
            {
                brokenFileNameQueue << CrtFlNm ; //加入到破损文件名列表中。
            } //if (fileInfo.exists ()==false) //不存在。在这两个条件下，认为是遇到破损文件名了。
        } //if (removeResult==false) //删除失败。

        QByteArray fileNameByteArray=fileInfo.fileName ().toUtf8 (); //DEbug.

        statusBar()->showMessage(tr("Deleting %1").arg(CrtFlNm)); //显示状态。
    } //else //The queue is not empty.
} //void FakeImageEliminator::Delete1File() //!<Delete timer timed out,then delete 1 file.

/*!
 * \brief ThumbnailsDeleter::connectSignals 连接信号槽。
 */
void GeneralCleaner::connectSignals()
{
    connect (&startWorkTimer,&QTimer::timeout,this,&GeneralCleaner::startWork); //定时器超时，则开始工作。
    connect(&subDirsFutureWatcher,&QFutureWatcher<QStringList>::finished,this,&GeneralCleaner::scanDirsNextLevel); //扫描下一个层次的子目录。
    connect(&fileListFutureWatcher, &QFutureWatcher<QStringList>::finished, this, &GeneralCleaner::startRecognizeFile); //开始识别一个个的文件。
    connect(&fileListFutureWatcher, &QFutureWatcher<QStringList>::progressValueChanged, this, &GeneralCleaner::updateListFileProgress); //列出文件的进度发生变化，则更新进度值。
    connect (rangeSortSearch.getSignalProxy (),&PaSignalProxy::finished,this,&GeneralCleaner::startDelete); //搜索完毕，则开始删除。
    connect(rangeSortSearch.getSignalProxy (),&PaSignalProxy::progressChanged,this,&GeneralCleaner::updateSearchProgress); //搜索进度发生变化，则更新搜索进度。

    connect(&DltTimer,SIGNAL(timeout()),this,SLOT(Delete1File())); //Delete timer timed out,then delete 1 file.

    connect (&CrtPrc,(void (QProcess::*)(int,QProcess::ExitStatus))&QProcess::finished,this,&GeneralCleaner::reportTunnelFinish); //隧道进程结束，则报告状态。

    connect(this, &GeneralCleaner::finished, this, &GeneralCleaner::close); //完毕，则关闭窗口。
} //void ThumbnailsDeleter::connectSignals()

/*!
 * \brief Sstm::reportTunnelFinish 报告隧道进程的终止事件。隧道进程结束，则报告状态。
 * \param extCd 退出代码。
 */
void GeneralCleaner::reportTunnelFinish(int extCd)
{
    Q_UNUSED(extCd); //不使用这个参数。

    QProcess * crtPrc=(QProcess *)sender(); //获取信号的发送者。

    QByteArray prcOtptBtAr=crtPrc->readAll (); //全部内容读取。

    QString prcOtpt=QString::fromUtf8 (prcOtptBtAr); //转换成字符串。


    //一行行地分析：
    QStringList lines=prcOtpt.split ("\n"); //分割成多行。

    for(QString currentLine:lines) //一行行地处理。
    {
        QStringList inodeNameList=currentLine.split (" "); //以空格分割。

        if (inodeNameList.size ()>1) //是有空格分割的。
        {
            quint64 inode=inodeNameList.at (0).toUInt(); //获取索引编号。
            QString fileName=inodeNameList.at(1); //获取文件名。

            QString absoluteFileName=currentBrokenFileDirPath+fileName; //构造绝对路径文件名。

            cout << __FILE__ << ", " << __LINE__ << ", " << __func__ << ", broken file absolute path: " << absoluteFileName.toStdString ()<< ", whole amount: " << FilesQueue.size() << endl; //Debug.


            QFileInfo absoluteFileInfo(absoluteFileName);

            if (absoluteFileInfo.exists ()) //存在。文件名未破损。
            {

            } //if (absoluteFileInfo.exists ()) //存在。文件名未破损。
            else //文件名破损。
            {
                deleteBrokenFileByInode(inode); //利用索引编号删除这个破损文件。
            } //else //文件名破损。


        } //if (inodeNameList.size ()>1) //是有空格分割的。

    } //for(QString currentLine:lines) //一行行地处理。

    delete1BrokenFileName (); //删除下一个破损文件名的文件。
} //void Sstm::reportTunnelFinish(int extCd) //!<隧道进程结束，则报告状态。


/*!
 * \brief TrashCleaner::startDeleteBrokenFileName 开始删除具有破损文件名的文件。
 */
void GeneralCleaner::startDeleteBrokenFileName()
{
    delete1BrokenFileName(); //删除一个具有破损文件名的文件。
} //void TrashCleaner::startDeleteBrokenFileName()

/*!
 * \brief ThumbnailsDeleter::startDelete 搜索完毕，则开始删除。
 */
void GeneralCleaner::startDelete()
{
    QStringList oldFiles=rangeSortSearch.getResult (); //获取结果。

    cout << __FILE__ << ", " << __LINE__ << ", " << __func__ << ", target amount: " << oldFiles.length() << ", whole amount: " << FilesQueue.size() << endl; //Debug.
    
    

    oldThumbnailFiles.append(oldFiles);

    DltTimer.start(); //Start the delete timer.

    statusBar ()->showMessage (tr("Deleting files")); //显示动作。
} //void ThumbnailsDeleter::startDelete()

/*!
 * \brief FakeImageEliminator::scanDirsNextLevel 扫描下一个层次的子目录。
 */
void GeneralCleaner::scanDirsNextLevel()
{
    QFuture<QStringList> subDirFutr=subDirsFutureWatcher.future (); //获取未来对象。

    QStringList subDirs=subDirFutr.result(); //获取扫描到的结果。

    if (subDirs.size ()) //有新结果。
    {
        if (subDirScanTime.elapsed()>=MaxSubDirScanTime) //扫描子目录的时间过长。
        {
            listDirFiles(); //开始列出文件。
        } //if (subDirScanTime.elapsed()>=MaxSubDirScanTime) //扫描子目录的时间过长。
        else //扫描子目录的时间并不长。
        {
            DirsQueue.append(subDirs); //将当前扫描到的子目录列表追加到整个要扫描的目录列表中。
            
            scanningDirList.clear (); //清空当前正在扫描的目录列表。
            scanningDirList.append(subDirs); //加入到当前正在扫描的目录列表中。
            
            scanSubDir(scanningDirList); //扫描子目录。
            
        } //else //扫描子目录的时间并不长。
        
    } //if (subDirs.size ()) //有新结果。
    else //没有新结果，则应当进行下一步骤的扫描了。扫描各个目录中的文件。
    {
        listDirFiles(); //开始列出各个子目录下的文件。
    } //else //没有新结果，则应当进行下一步骤的扫描了。扫描各个目录中的文件。
} //void FakeImageEliminator::scanDirsNextLevel()

GeneralCleaner::GeneralCleaner(const QString directoryName , QWidget *parent) : QMainWindow(parent), ui(new Ui::GeneralCleaner)
{
    ThumbnailsDirName=directoryName;
    
    ui->setupUi (this); //初始化用户界面。

    initializeMembers(); //初始化成员变量。

    startWorkTimer.start(); //启动enet轮询定时器。

    connectSignals(); //连接信号槽。
}

/*!
 * \brief FakeImageEliminator::scanSubDir 扫描子目录。
 * \param scanningDirList2Scan 要扫描其子目录的目录名列表。
 */
void GeneralCleaner::scanSubDir(QList<QString> scanningDirList2Scan)
{
    scanSubDirPass++; //遍数增加。
    
    QFuture<QStringList> subDirs=QtConcurrent::mappedReduced(scanningDirList2Scan,getSubDirs,addToSubDirList); //启动一个并行映射归并过程。
    subDirsFutureWatcher.setFuture(subDirs); //设置未来对象。
    
    statusBar()->showMessage(tr("Scanning sub directories, pass %1, directories amount %2, elapsed time: %3").arg(scanSubDirPass).arg(scanningDirList2Scan.size()).arg(subDirScanTime.elapsed())); //显示状态。
} //void FakeImageEliminator::scanSubDir(QList<QString> scanningDirList2Scan)
