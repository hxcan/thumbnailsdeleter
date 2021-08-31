#ifndef __MAINLOGIC_H__
#define __MAINLOGIC_H__

//#include <iostream>
//using namespace std;
//#include <vector>

#include "ThumbnailsDeleter.h" //ThumbnailsDeleter
#include "TrashCleaner.h" //TrashCleaner
#include "RpmbuildCleaner.h" //RpmbuildCleaner
#include "ManageWindow.h" //ManageWindow

class MainLogic: public QObject
{
    Q_OBJECT
    
public:
    friend QDataStream & operator>>(QDataStream &,MainLogic&); //!<从数据流中输入。
    friend QDataStream & operator<<(QDataStream &,const MainLogic&); //!<输出到数据流中。
    MainLogic(); //构造函数。
    void SetAscii(quint8 AsciiMa2BSet); //设置此项的Ascii码。
    quint8 GetValue(); //!<返回此项的字节值。

private:
    void remember1Finished(); //!<完成一项，则记录一项。
    void connectSignals(); //!<连接信号。
    ThumbnailsDeleter PbSrv; //!<缩略图删除器窗口。
    TrashCleaner trashPbSrv; //!<回收站删除器窗口。
    ManageWindow manageWindowtrashPbSrv; //!<管理窗口。
    RpmbuildCleaner rpmbuildClearntrashPbSrv; //!<RPMBUILD删除器窗口。
    
    quint8 ByteValue=0; //!<已完成的任务数。
}; //class DictItem

#endif // __DICITEM_H__
