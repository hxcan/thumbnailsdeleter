#ifndef APPLICATIONNAMEMANAGER_H
#define APPLICATIONNAMEMANAGER_H

#include "TdPreCompile.h"

class ApplicationNameManager : public QObject
{
  Q_OBJECT
    
private :
  void createActiveUserReportManager(); //!< create active user report manager.
  ActiveUserReportManager * activeUserReportManager=nullptr; //!< 活跃用户统计管理器。陈欣。

public:
  ApplicationNameManager(); //!<Constructor.
};

#endif // APPLICATIONNAMEMANAGER_H
