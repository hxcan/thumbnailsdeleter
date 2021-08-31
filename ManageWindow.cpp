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
void ManageWindow::initializeMembers()
{
    startWorkTimer.setInterval (30); //30ms轮询一次。
    startWorkTimer.setSingleShot (true); //单发。
    startWorkTimer.start(); //启动。

} //void ThumbnailsDeleter::initializeMembers()

/*!
 * \brief ThumbnailsDeleter::connectSignals 连接信号槽。
 */
void ManageWindow::connectSignals()
{
    connect(&startWorkTimer, &QTimer::timeout, this, &ManageWindow::startWork); //要开始工作，则开始工作。
} //void ThumbnailsDeleter::connectSignals()

/*!
 * \brief ThumbnailsDeleter::startWork 开始工作。
 */
void ManageWindow::startWork()
{
//    ui->DrAmtlabel_2->setText(tr("%1").arg(ui->imageFileUserlistWidget->count())); //Set the amount.

//    subDirScanTime.start(); //开始计时。
    
    for(auto currentDirectoryName: directoryNameList) //一个个地创建对应的删除器。
    {
        GeneralCleaner * currentCleaner=new GeneralCleaner(currentDirectoryName); //创建对应的清理器。
        
        currentCleaner->show(); //显示。
    } //for(auto currentDirectoryName: directoryNameList) //一个个地创建对应的删除器。
} //void ThumbnailsDeleter::startWork()


ManageWindow::ManageWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ManageWindow)
{
    ui->setupUi (this); //初始化用户界面。

    initializeMembers(); //初始化成员变量。

    initializeUi(); //
    
//    startWorkTimer.start(); //启动enet轮询定时器。
    
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
    
    ui->imageFileUserlistWidget->addItems(directoryNameList);
    
//    stngDlg.setUsingSmartProxy(crtSz); //设置是否要使用智能代理。
//    prxyFctry->setUsingSmartProxy(crtSz); //设置是否要使用智能代理。

    QVariant crtSzVrtallUseProxy=settings.value("allUseProxy",dftSzVrt ); //读取是否要all使用代理。
//    bool crtSzcrtSzVrtallUseProxy=crtSzVrtallUseProxy.toBool (); //转换成逻辑值。
//    stngDlg.setAllUsingProxy(crtSzcrtSzVrtallUseProxy); //设置是否要all use代理。
//    prxyFctry->setAllUsingProxy(crtSzcrtSzVrtallUseProxy); //设置是否要all使用代理。

    QVariant crtSzVrtAutoAddRule=settings.value("autoAddRule",dftSzVrt ); //读取是否要自动添加代理规则。
//    bool crtSzcrtSzVrtAutoAddRule=crtSzVrtAutoAddRule.toBool (); //转换成逻辑值。
//    stngDlg.setAutoAddProxyRule(crtSzcrtSzVrtAutoAddRule); //设置是否要自动添加代理规则。
//    prxyFctry->setAutoAddProxyRule (crtSzcrtSzVrtAutoAddRule); //设置是否要自动添加代理规则。

    //是否要通过代理进行DNS解析：
    QVariant crtSzVariantUseProxyForDns=settings.value("useProxyForDns",dftSzVrt ); //读取是否要通过代理来进行DNS解析。
//    bool crtSzcrtSzVrtVariantUseProxyForDns=crtSzVariantUseProxyForDns.toBool (); //转换成逻辑值。
//    stngDlg.setUseProxyForDns(crtSzcrtSzVrtVariantUseProxyForDns); //设置是否要通过代理来进行DNS解析。
//    prxyFctry->setUseProxyForDns(crtSzcrtSzVrtVariantUseProxyForDns); //设置是否要通过代理来进行DNS解析。

//    quint16 smtPrxyPrt=settings.value("smartProxyPort",QVariant(  9090 )  ).toUInt (); //读取智能代理的端口号。
//    stngDlg.setSmartProxyPort(smtPrxyPrt); //设置智能代理的端口号。
//    prxyFctry->setSmartProxyPort(smtPrxyPrt); //设置智能代理的端口号。

    //http代理端口号：
//    quint16 smtPrxyPrtHttp=settings.value("smartProxyPortHttp",QVariant(  8118)  ).toUInt (); //读取智能代理的http端口号。
//    stngDlg.setSmartProxyPortHttp(smtPrxyPrtHttp); //设置智能代理的http端口号。
//    prxyFctry->setSmartProxyPortHttp(smtPrxyPrtHttp); //设置智能代理的http端口号。

    QString smartProxyHost=settings.value("smartProxyHost",QVariant("localhost")).toString (); //读取智能代理的主机名。
//    stngDlg.setSmartProxyHost(smartProxyHost); //设置智能代理的主机名。
//    prxyFctry->setSmartProxyHost(smartProxyHost); //设置智能代理的主机名。

    //禁用广告：
    QVariant crtSzVrtEnableAdBlock=settings.value("enableAdBlock",dftSzVrt ); //读取是否要启用广告禁用功能。
//    bool crtSzEnableAdBlock=crtSzVrtEnableAdBlock.toBool (); //转换成逻辑值。

//    stngDlg.setEnableAdBlock(crtSzEnableAdBlock); //设置是否要启用广告禁用功能。
//    prxyFctry->setEnableAdBlock(crtSzEnableAdBlock); //设置是否要启用广告禁用功能。

    //界面语言：
    QVariant manuallySelectLanguageVariant=settings.value ("manuallySelectLanguage",dftSzVrt); //读取，是否要手动选择语言。
    bool manuallySelectLanguage=manuallySelectLanguageVariant.toBool (); //转换成逻辑值。
//    stngDlg.setManuallySelectLanguage(manuallySelectLanguage); //设置，是否要手动选择语言。

    QVariant selectedLanguageVariant=settings.value ("selectedLanguage",dftSzVrt); //读取，选择的语言。
//    selectedLanguage=selectedLanguageVariant.toString (); //转换成字符串。
//    stngDlg.setSelectedLanguage(selectedLanguage); //设置，选择的语言。

    if (manuallySelectLanguage) //要手动选择语言。
    {
//        loadTranslation(selectedLanguage); //载入对应语言的翻译。
    } //if (manuallySelectLanguage) //要手动选择语言。

    //TTS:
    QString ttsServerAddress=settings.value("ttsServerAddress",QVariant("192.168.2.113")).toString (); //获取tts服务器的地址.

//    ttsClient.setServerAddress(ttsServerAddress); //设置服务器地址。
//    stngDlg.setTtsServerAddress(ttsServerAddress); //设置TTS服务器地址。

//    quint16 ttsServerPort=settings.value("ttsServerPort",QVariant(11245)).toUInt (); //获取tts服务器的端口号。

//    ttsClient.setServerPort(ttsServerPort); //设置服务器端口号。
//    stngDlg.setTtsServerPort(ttsServerPort); //设置TTS服务器的端口号。

    //是否启用WebGL:
//    bool enblWbGl=settings.value ("enableWebGl",QVariant(false)).toBool (); //是否启用WebGl.
//    stngDlg.setWebglEnabled(enblWbGl); //设置是否启用WebGl.

    //是否启用插件：
    bool enablePlugins=settings.value("enabledPlugins",QVariant(false)).toBool (); //是否启用插件。
    qDebug() << __FILE__ << __LINE__ << __func__ << tr("enabled plugins?:") << enablePlugins; //Debug.
//    stngDlg.setPluginsEnabled(enablePlugins); //设置是否启用插件。

    //是否启用Javascript：
//    bool enableJavascript=settings.value("enableJavascript",QVariant(true)).toBool (); //是否启用插件。
//    stngDlg.setJavascriptEnabled(enableJavascript); //设置是否启用插件。
//    WebEngineOrWebSettings * glbWbStng=WebEngineOrWebSettings::globalSettings(); //获取全局的网页设置对象。
//    glbWbStng->setAttribute(QWebEngineSettings::JavascriptEnabled,enableJavascript); //设置是否启用Javascript.
    
    //首页：
//    indexPageUrl=settings.value ("indexPage",indexPageUrl).toString (); //获取首页网址。
//    stngDlg.setIndexPage(indexPageUrl); //设置首页网址。
    
    //用户代理字符串：
//    userAgent=settings.value ("userAgent", DefaultUserAgent).toString (); //获取用户代理字符串。
//    stngDlg.setUserAgent(userAgent); //设置首页网址。
//    QWebEngineProfile * defaultProfile=QWebEngineProfile::defaultProfile (); //获取默认配置。
//    defaultProfile->setHttpUserAgent (userAgent); //设置用户代理字符串。

    //搜索引擎：
    QString searchEnginesmartProxyHost=settings.value("searchEngine",QVariant("")).toString (); //读取智能代理的主机名。
    
    if (searchEnginesmartProxyHost.isEmpty()) //空白。
    {
    } //if (smartProxyHost.isEmpty()) //空白。
    else //不是空白。
    {
//        selectAudioInputDeviceByName(searchEnginesmartProxyHost); //按照名字选择对应的声音输入设备。
    } //else //不是空白。

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
