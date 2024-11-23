#ifndef __MAINLOGIC_H__
#define __MAINLOGIC_H__

#include "ManageWindow.h" //ManageWindow

class MainLogic: public QObject
{
  Q_OBJECT
    
public:
  MainLogic(); //构造函数。
  void SetAscii(quint8 AsciiMa2BSet); //设置此项的Ascii码。
  quint8 GetValue(); //!<返回此项的字节值。

private:
  void remember1Finished(); //!<完成一项，则记录一项。
  ManageWindow manageWindowtrashPbSrv; //!<管理窗口。
  quint8 ByteValue=0; //!<已完成的任务数。
}; //class DictItem

#endif // __DICITEM_H__
