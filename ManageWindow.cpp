#include "TdPreCompile.h" //QFile


#include "CommonHeader.h" //DataType
//#include "ui_ThumbnailsDeleter.h"
#include "mapReduceFunctions.h" //getSubDirs
#include "FileTimeComparator.h" //FileTimeComparator
#include "GeneralCleaner.h" //GeneralCleaner

/*!
 * \brief ThumbnailsDeleter::initializeMembers 初始化成员变量。
 */
void ManageWindow::initializeMembers()
{
  startWorkTimer.setInterval (236000); // 236000 s 轮询一次。
  startWorkTimer.setSingleShot (true); //单发。
  startWorkTimer.start(); //启动。

  generalCleanerCreatingTimer.setInterval (19);
//  generalCleanerCreatingTimer

  memoryMonitor.setLowMemoryBehavior(LowMemoryBehavior::Quit); // Quit when memory is low.
} //void ThumbnailsDeleter::initializeMembers()

/*!
 * \brief ThumbnailsDeleter::connectSignals 连接信号槽。
 */
void ManageWindow::connectSignals()
{
  connect(&startWorkTimer, &QTimer::timeout, this, &ManageWindow::startWork); //要开始工作，则开始工作。

  connect (&generalCleanerCreatingTimer, &QTimer::timeout, this, &ManageWindow::create1GeneralCleaner); // Create one general cleaner each time.
} //void ThumbnailsDeleter::connectSignals()

/*!
 * \brief ManageWindow::cleanNow Do the clean now.
 */
void ManageWindow::cleanNow()
{
  startWork (); // Start work.
} // void ManageWindow::cleanNow()

/*!
 * \brief ManageWindow::create1GeneralCleaner Create one general cleaner each time.
 */
void ManageWindow::create1GeneralCleaner()
{
  if (directoryNameListCounter< directoryNameList.size ()) // Not fully created
  {
      auto currentDirectoryName = directoryNameList.at (directoryNameListCounter); // get the directory path.
//      {
        createGeneralCleaner(currentDirectoryName); // Create the coresponding general cleaner.
//      } //for(auto currentDirectoryName: directoryNameList) //一个个地创建对应的删除器。

        directoryNameListCounter++;

  } // if (directoryNameListCounter< directoryNameList.size ()) // Not fully created
  else // Fully created
  {
    generalCleanerCreatingTimer.stop ();
  } // else // Fully created
} // void ManageWindow::create1GeneralCleaner()

/*!
 * \brief ThumbnailsDeleter::startWork 开始工作。
 */
void ManageWindow::startWork()
{
  directoryNameListCounter=0;

  generalCleanerCreatingTimer.start(); // STart the timer of creating general clieaner.

//  for(auto currentDirectoryName: directoryNameList) //一个个地创建对应的删除器。
//  {
//    createGeneralCleaner(currentDirectoryName); // Create the coresponding general cleaner.
//  } //for(auto currentDirectoryName: directoryNameList) //一个个地创建对应的删除器。
} //void ThumbnailsDeleter::startWork()

/*!
 * \brief ManageWindow::createGeneralCleaner Create the coresponding general cleaner.
 * \param currentDirectoryName The directory path to clean.
 */
void ManageWindow::createGeneralCleaner(const QString & currentDirectoryName)
{
  GeneralCleaner * currentCleaner=new GeneralCleaner(currentDirectoryName); //创建对应的清理器。

  currentCleaner->show(); //显示。
} // void ManageWindow::createGeneralCleaner(const QString & currentDirectoryName)

ManageWindow::ManageWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ManageWindow)
{
  ui->setupUi (this); //初始化用户界面。

  initializeMembers(); //初始化成员变量。

  initializeUi(); //
    
  loadDirectoryNameList(); //载入目录名字列表。

  connectSignals(); //连接信号槽。
}

/*!
 * \brief DisplayHead::initializeUi 
 */
void ManageWindow::initializeUi()
{
  addActions(); //
}

/*!
 * \brief SWebPageWidget::addActions 
 */
void ManageWindow::addActions()
{
  QAction * focusSearchEngineAction=new QAction(this); //
  focusSearchEngineAction->setText (tr("")); //
  focusSearchEngineAction->setShortcut (QKeySequence("Ctrl+Q"));

  addAction (focusSearchEngineAction); //

  connect (focusSearchEngineAction,&QAction::triggered,this, &ManageWindow::requestQuit); //
} //void SWebPageWidget::addActions()

/*!
 * \brief DisplayInterface::requestQuit 
 */
void ManageWindow::requestQuit()
{
    QCoreApplication::quit();
} //void DisplayInterface::requestQuit()


/*!
 * \brief ManageWindow::saveDirectoryNameList 保存列表。
 */
void ManageWindow::saveDirectoryNameList()
{
  QSettings settings; //设置信息储存对象。

  settings.beginGroup("SBrowser"); //开始分组。

  //智能代理：
  QVariant crtSz=QVariant(directoryNameList); //是否使用智能代理。
  settings.setValue("directoryNameList", crtSz); //记录是否使用智能代理。
//    prxyFctry->setUsingSmartProxy (stngDlg.isUsingSmartProxy ()); //设置是否要使用智能代理。


//    QVariant crtSzAllProxy=QVariant(stngDlg.isAllUsingProxy()); //是否all 使用代理。
//    settings.setValue("allUseProxy", crtSzAllProxy); //记录是否all使用代理。
//    prxyFctry->setAllUsingProxy (stngDlg.isAllUsingProxy ()); //设置是否要all使用代理。


//    QVariant crtSzAutoAddProxyRule=QVariant(stngDlg.isAutoAddProxyRule()); //是否自动添加代理规则。
//    settings.setValue("autoAddRule", crtSzAutoAddProxyRule); //记录是否自动添加代理规则。
//    prxyFctry->setAutoAddProxyRule (stngDlg.isAutoAddProxyRule ()); //设置是否自动添加代理规则。


  //是否要通过代理进行DNS解析：
//    QVariant crtSzVariantUseProxyForDns=QVariant(stngDlg.isUseProxyForDns()); //是否要通过代理进行DNS解析。
//    settings.setValue("useProxyForDns", crtSzVariantUseProxyForDns); //记录是否自动添加代理规则。
//    prxyFctry->setUseProxyForDns (stngDlg.isUseProxyForDns ()); //是否要通过代理进行DNS解析。


//    QVariant crtPos=QVariant(stngDlg.getSmartProxyPort()); //智能代理的端口号。
//    settings.setValue("smartProxyPort", crtPos); //记录智能代理的端口号。
//    prxyFctry->setSmartProxyPort(stngDlg.getSmartProxyPort()); //设置智能代理的端口号。

  //http代理端口号：
//    QVariant crtPosHttp=QVariant(stngDlg.getSmartProxyPortHttp()); //智能代理的http端口号。
//    settings.setValue("smartProxyPortHttp", crtPosHttp); //记录智能代理的http端口号。
//    prxyFctry->setSmartProxyPortHttp(stngDlg.getSmartProxyPortHttp()); //设置智能代理的http端口号。



//    QVariant smartProxyHost=QVariant(stngDlg.getSmartProxyHost()); //智能代理的主机名。
//    settings.setValue ("smartProxyHost",smartProxyHost); //记录智能代理的主机名。
//    prxyFctry->setSmartProxyHost(stngDlg.getSmartProxyHost()); //设置智能代理的主机名。


  //禁用广告：
//    QVariant crtSzVrtEnableAdBlock=stngDlg.getEnableAdBlock(); //读取是否要启用广告禁用功能。
//    settings.setValue ("enableAdBlock",crtSzVrtEnableAdBlock); //保存，是否要启用广告禁用功能。
//    prxyFctry->setEnableAdBlock (stngDlg.getEnableAdBlock()); //设置，是否要启用广告禁用功能。

  //界面语言：
//    QVariant manuallySelectLanguageVariant(stngDlg.getManuallySelectLanguage()); //是否手动选择界面语言。
//    settings.setValue ("manuallySelectLanguage",manuallySelectLanguageVariant); //记录，是否手动选择界面语言。

//    QVariant selectedLanguageVariant(stngDlg.getSelectedLanguage()); //获取选择的语言。
//    settings.setValue ("selectedLanguage",selectedLanguageVariant); //记录，选择的语言。

//    if (stngDlg.getManuallySelectLanguage()) //要手动选择语言。
  {
//        loadTranslation(stngDlg.getSelectedLanguage()); //载入对应语言的翻译。
  } //if (stngDlg.getManuallySelectLanguage()) //要手动选择语言。




  //TTS:
//    QVariant ttsServerAddress=QVariant(stngDlg.getTtsServerAddress()); //获取TTS服务器的地址。

//    settings.setValue("ttsServerAddress",ttsServerAddress); //tts服务器的地址.

//    QVariant ttsServerPort=QVariant(stngDlg.getTtsServerPort()); //获取TTS服务器的端口号。

//    settings.setValue("ttsServerPort",ttsServerPort); //tts server's port.

//    ttsClient.setServerAddress (stngDlg.getTtsServerAddress ()); //设置TTS服务器的地址。
//    ttsClient.setServerPort (stngDlg.getTtsServerPort ()); //设置TTS服务器的端口号。


  //WebGl:
//    QVariant enblWbGl=QVariant(stngDlg.getWebGlEnabled()); //是否启用WebGl.
//    settings.setValue ("enableWebGl",enblWbGl); //是否启用WebGl.


  //插件：
//    QVariant enablePlugins=QVariant(stngDlg.getPluginsEnabled()); //是否启用插件。
//    settings.setValue ("enabledPlugins",enablePlugins); //设置值，是否启用插件。

  //是否启用Javascript：
//    bool enableJavascript=stngDlg.getJavascriptEnabled(); //是否启用插件。
//    QVariant enableJavascriptVariant=QVariant(enableJavascript);
//    settings.setValue("enableJavascript",enableJavascriptVariant);
//    WebEngineOrWebSettings * glbWbStng=WebEngineOrWebSettings::globalSettings(); //获取全局的网页设置对象。
//    glbWbStng->setAttribute(QWebEngineSettings::JavascriptEnabled,enableJavascript); //设置是否启用Javascript.
    
  //首页：
//    QVariant indexPage=QVariant(stngDlg.getIndexPage()); //首页网址。
//    settings.setValue ("indexPage",indexPage); //首页网址。
//    indexPageUrl=stngDlg.getIndexPage(); //记录首页网址。

  //用户代理字符串：
//    QVariant userAgentVariant=QVariant(stngDlg.getUserAgent ()); //获取用户代理字符串。
//    settings.setValue ("userAgent", userAgentVariant); //用户代理字符串。
//    userAgent=stngDlg.getUserAgent (); //记录用户代理字符串。
//    QWebEngineProfile * defaultProfile=QWebEngineProfile::defaultProfile (); //获取默认配置。
//    defaultProfile->setHttpUserAgent (userAgent); //设置用户代理字符串。

  //搜索引擎：
//    QString searchEngineName=stngDlg.getSearchEngineName(); //获取搜索引擎名字。
//    QVariant searchEnginesmartProxyHost=QVariant(searchEngineName); //智能代理的主机名。
//    settings.setValue ("searchEngine",searchEnginesmartProxyHost); //记录智能代理的主机名。

  settings.endGroup(); //关闭分组。

  settings.sync(); //同步。
} //void ManageWindow::saveDirectoryNameList()

/*!
 * \brief ManageWindow::addInternalDirectoryNameList Add internal directory name list, if not in list.
 */
void ManageWindow::addInternalDirectoryNameList()
{
  auto ThumbnailsDirName=QDir::homePath ()+"/.cache/thumbnails/"; //缩略图目录名。

  if (directoryNameList.contains(ThumbnailsDirName)) // Contains.
  {

  } // if (directoryNameList.contains(ThumbnailsDirName)) // Contains.
  else // Not contains.
  {
    directoryNameList << ThumbnailsDirName; // Add to list.
  }      // else // Not contains.

  ThumbnailsDirName=QDir::homePath ()+"/.local/share/Trash/files/"; //缩略图目录名。

  if (directoryNameList.contains(ThumbnailsDirName)) // Contains.
  {

  } // if (directoryNameList.contains(ThumbnailsDirName)) // Contains.
  else // Not contains.
  {
    directoryNameList << ThumbnailsDirName; // Add to list.
  }      // else // Not contains.

  ThumbnailsDirName=QDir::homePath ()+"/rpmbuild/"; //缩略图目录名。

  if (directoryNameList.contains(ThumbnailsDirName)) // Contains.
  {

  } // if (directoryNameList.contains(ThumbnailsDirName)) // Contains.
  else // Not contains.
  {
    directoryNameList << ThumbnailsDirName; // Add to list.
  }      // else // Not contains.
} // void ManageWindow::addInternalDirectoryNameList()

/*!
 * \brief ManageWindow::loadDirectoryNameList 载入目录名字列表。
 */
void ManageWindow::loadDirectoryNameList()
{
  QSettings settings; //设置信息。s

  settings.beginGroup("SBrowser"); //主程序。

  QVariant dftSzVrt=QVariant(QSize(400, 400)); //默许窗口尺寸。

  //智能代理：
  QVariant crtSzVrt=settings.value("directoryNameList", dftSzVrt ); //读取是否要使用智能代理。
  directoryNameList=crtSzVrt.toStringList(); //转换成字符串列表。
    
  addInternalDirectoryNameList(); // Add internal directory name list, if not in list.

  ui->imageFileUserlistWidget->addItems(directoryNameList);
    
  settings.endGroup(); //关闭分组。
} //void ManageWindow::loadDirectoryNameList()

/*!
 * \brief ManageWindow::addDirectory 添加一个待处理的目录。
 */
void ManageWindow::addDirectory()
{
  QString directoryName=QFileDialog::getExistingDirectory(); //浏览选择到目录路径。
    
  if (directoryName.isEmpty()) //是空白的。
  {
  } //if (directoryName.isEmpty()) //是空白的。
  else //不是空白的。
  {
    directoryNameList << directoryName;
        
    ui->imageFileUserlistWidget->addItem(directoryName); //添加到列表中。
        
        saveDirectoryNameList(); //保存列表。
    } //else //不是空白的。
} //void ManageWindow::addDirectory()

/*!
 * \brief ManageWindow::removeDirectory 删除一个待处理的目录。
 */
void ManageWindow::removeDirectory()
{
    auto index=ui->imageFileUserlistWidget->currentRow (); //获取当前行。

    if (index>=0) //有选中的行。
    {
      auto currentItem=ui->imageFileUserlistWidget->takeItem (index); //删除。



        directoryNameList.removeOne (currentItem->text()); //删除条目。


        saveDirectoryNameList (); //保存目录列表。
    } //if (index>=0) //有选中的行。

} //void ManageWindow::removeDirectory()
