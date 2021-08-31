#ifndef MANAGEWINDOW_H
#define MANAGEWINDOW_H

#include "TdPreCompile.h" //QTcpServer

#include "RangeSortSearch.h" //RangeSortSearch

#include "ui_ManageWindow.h" //TrashCleaner

namespace Ui {
class ManageWindow;
}

class ManageWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ManageWindow(QWidget *parent = 0);

private slots:
    void addDirectory(); //!<添加一个待处理的目录。
    void removeDirectory(); //!<删除一个待处理的目录。

private:
    void initializeUi(); //!<
    void startWork(); //!<开始工作。
    void saveDirectoryNameList(); //!<保存列表。
    QStringList directoryNameList; //!<目录名字列表。
    void loadDirectoryNameList(); //!<载入目录名字列表。
    QString currentBrokenFileDirPath; //!<当前正在处理的损坏文件名文件的目录路径。
    QString SshCmd="ls"; //!<ssh命令。
    QString FindCmd="find"; //!<find命令。
    QQueue<QString> brokenFileNameQueue; //!<破损文件名列表。
    qint32 MaxSubDirScanTime=10*10000; //!<扫描子目录的最长时间。毫秒。
    void addActions(); //!<
    void connectSignals(); //!<连接信号槽。
    void initializeMembers(); //!<初始化成员变量。
    QTimer startWorkTimer; //!<触发开始工作动作的定时器。
    Ui::ManageWindow *ui; //!<用户界面。
    void requestQuit(); //!<
    
signals:
    void finished(); //!<信号，已经完成。
};

#endif //
