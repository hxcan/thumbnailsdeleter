#include "TdPreCompile.h" 

#include "ApplicationNameManager.h" //ApplicationNameManager

/*!
 * \brief ApplicationNameManager::ApplicationNameManager Constructor.
 */
ApplicationNameManager::ApplicationNameManager()
{
  QCoreApplication::setOrganizationName("StupidBeauty"); //
  QCoreApplication::setOrganizationDomain("stupidbeauty.com"); //
  QCoreApplication::setApplicationName("ThumbnailsDeleter"); //

  createActiveUserReportManager(); // 创建管理器，活跃用户统计。陈欣
} //ApplicationNameManager::ApplicationNameManager()

/**
* 创建管理器，活跃用户统计。陈欣
*/
void ApplicationNameManager::createActiveUserReportManager()
{
  if (activeUserReportManager==nullptr) // 还不存在管理器。
  {
    activeUserReportManager=new ActiveUserReportManager(); // 创建管理器。

    activeUserReportManager->startReportActiveUser("com.stupidbeauty.thumbnailsdeleter"); // 开始报告活跃用户。
  } //if (activeUserReportManager==null)
} //private void createActiveUserReportManager()

