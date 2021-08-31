#ifndef DATATYPE_H
#define DATATYPE_H

namespace DataType
{
/*!
  *@brief 数据包中的数据类型。
  */
enum DataType
{
    ConnectPeer=1, //!<连接到对端。
    IdReport=2, //!<编号报告。
    AssignId=7, //!<分配编号。
    HolePunchRequest=8, //!<请求指挥打洞。
    InitTunnel=10, //!<启动隧道。
    TcpSktRelay=12, //!<转发TCP数据包。
    DiscntNotify=14, //!<通知断开连接。
    PeerNotFound=15, //!<节点未找到。
    HeartBitNegative=17, //!<被动心跳包。
    RelayerNotExist=20, //!<转发器不存在。
    LoginInfo=21, //!<登录信息。
    LoginResult=22, //!<登录结果。
    VideoRecorderListRequest=23, //!<请求获取视频录像机列表。
    VideoRecorderList=24, //!<发送视频录像机列表。
    ServerRelayRequest=25, //!<请求转发数据包。
    ServerRelayNotify=26, //!<转发数据包通知。
    RelayThis=27, //!<转发这个数据包。
    TcpSktRelayCompressed=47, //!<转发经过压缩的TCP数据包。
    KickOffElseWhere=48, //!<相同的用户名在别的地方登录，踢掉了上次登录的客户端。
    AddFriendRequest=53, //!<请求添加好友。
    AddFriendRequestNotify=54, //!<通知：有人想要与你加为好友。
    AddFriendResponse=55, //!<对于添加好友的请求的回复。
    AddFriendResponseNotify=56, //!<对于添加好友的请求的回复通知。
    BoatInfo=57, //!<船信息。
    GateWayInfo=58, //!<网关信息。
    FinishTunnelOrder=59, //!<要求完成隧道。
    BeaconHeartBit=60, //!<灯塔的心跳包。
    BoatHeartBit=61, //!<船的心跳包。
    TunnelResult=62, //!<隧道开启结果。
    CreateTunnelRequest=63, //!<请求开启隧道。
    ListenResult=64, //!<P2pBeaconProxy的监听结果信息。
    FinishTunnelRequest=65, //!<请求完成隧道。
    ExternalIp=66, //!<外部IP通知。
    FriendList=70, //!<好友列表。
    DeleteFriendRequest=71 //!<请求删除好友。
}; //enum DataType
} //namespace DataType


#endif // DATATYPE_H
