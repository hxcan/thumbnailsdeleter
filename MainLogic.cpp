#include "MainLogic.h"
#include <vector>
using namespace std;

MainLogic::MainLogic()
{
  ByteValue=0;
    
  manageWindowtrashPbSrv.show (); //显示管理窗口。
} //DictItem::DictItem()

/*!
 * \brief MainLogic::remember1Finished 完成一项，则记录一项。
 */
void MainLogic::remember1Finished()
{
  ByteValue++; //计数。
    
  if (ByteValue>=3) //全部完成。
  {
//        QApplication::quit(); //退出。
  } //if (ByteValue>=3) //全部完成。
} //void MainLogic::remember1Finished()

quint8 MainLogic::GetValue()
{
  quint8 JieGuo=0; //结果。

  JieGuo=ByteValue;

  return JieGuo;
} //unsigned int DictItem::GetAscii()


void MainLogic::SetAscii(quint8 AsciiMa2BSet)
{
    ByteValue=AsciiMa2BSet;

	return;
} //void DictItem::SetAscii(unsigned int AsciiMa2BSet)
