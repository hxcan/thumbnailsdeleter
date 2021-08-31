#include "MainLogic.h"
#include <vector>
using namespace std;

MainLogic::MainLogic()
{
    ByteValue=0;
    
    PbSrv.show (); //显示。

    trashPbSrv.show (); //显示。

    rpmbuildClearntrashPbSrv.show (); //显示。
    

    manageWindowtrashPbSrv.show (); //显示管理窗口。
    
    connectSignals(); //连接信号。
} //DictItem::DictItem()

/*!
 * \brief MainLogic::connectSignals 连接信号。
 */
void MainLogic::connectSignals()
{
    connect(&PbSrv,&ThumbnailsDeleter::finished,this,&MainLogic::remember1Finished); //完成一项，则记录一项。
    connect(&trashPbSrv,&TrashCleaner::finished,this,&MainLogic::remember1Finished); //完成一项，则记录一项。
    connect(&rpmbuildClearntrashPbSrv,&RpmbuildCleaner::finished,this,&MainLogic::remember1Finished); //完成一项，则记录一项。
    
} //void MainLogic::connectSignals()

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

/*!
  *@brief 输出到数据流中。
  *@param TheOutputStream 数据流。
  *@param NmCd2Output 要输出的名片。
  */
QDataStream & operator<<(QDataStream & TheOutputStream,const MainLogic & NmCd2Output)
{
//    TheOutputStream << NmCd2Output.HeadPixmap; //输出正面图片。
//    TheOutputStream << NmCd2Output.TailPixmap; //输出背面图片。

    TheOutputStream << NmCd2Output.ByteValue; //输出字节的值。

    return TheOutputStream;
} //QDataStream & operator<<(QDataStream & TheOutputStream,const NameCard & NmCd2Output)

