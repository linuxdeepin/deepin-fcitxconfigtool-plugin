#ifndef FcitxConfigPlugin_H
#define FcitxConfigPlugin_H

#include "ddeInterface/namespace.h"
#include "ddeInterface/moduleinterface.h"
#include "ddeInterface/frameproxyinterface.h"
#include <QObject>
#include <QMessageBox>
#include <QWidget>
#include <QGridLayout>
#include <QMainWindow>


namespace DCC_NAMESPACE {
class FcitxConfigPlugin :public QObject, public DCC_NAMESPACE::ModuleInterface
{
    Q_OBJECT
    Q_INTERFACES(DCC_NAMESPACE::ModuleInterface)
    Q_PLUGIN_METADATA(IID ModuleInterface_iid FILE "ddeInterface/fcitxconfigplugin.json")
public:
    FcitxConfigPlugin();
    FcitxConfigPlugin(FrameProxyInterface *frameProxy) : ModuleInterface(frameProxy) {
    }
    ~FcitxConfigPlugin(){
    }

    // preInitialize会在模块初始化时被调用，用于模块在准备阶段进行资源的初始化；
    // preInitialize不允许进行高资源的操作；
    virtual void preInitialize(bool sync = false,FrameProxyInterface::PushType = FrameProxyInterface::PushType::Normal) {
        Q_UNUSED(sync)
    }

    // initialize初始化相应的模块，参数proxy用于Moudle向Frame信息查询和主动调用；
    // 返回Module的id；
    // initialize的时候不能做资源占用较高的操作；
    virtual void initialize(){

    }

    // reset module settings
    virtual void reset() {
    }

    ///
    /// \brief name
    /// your module name
    /// \return
    ///
    virtual const QString name() const {
        return QString("testPlugin");
    };

    ///
    /// \brief name
    /// 模块名，用于显示
    /// \return
    ///
    virtual const QString displayName() const
    {
        return QString("输入法配置");
    }

    ///
    /// \brief icon
    /// get module icon path
    /// \return
    ///
    virtual QIcon icon() const {
        return QIcon::fromTheme("fcitx");
    }

    ///
    /// \brief translationPath
    /// 获取多语言文件的路径，用以搜索
    /// \return QString
    ///
    virtual QString translationPath() const {
        return QString();
    }

    ///
    /// \brief showPage
    /// show specified module page
    /// \param pageName
    /// the page name
    ///
    virtual void showPage(const QString &pageName) {
        Q_UNUSED(pageName); }

    /// \brief load
    /// 当搜索到相关字段后，lead会被调用
    /// 如果可以正常显示则返回 0, 否则返回非0
    virtual int load(const QString &path) {
        Q_UNUSED(path);
        return 0;
    }

    virtual QStringList availPage() const {
        return QStringList(); }

    /**
     * @brief path
     * @return 插件级别及二级菜单插件所属模块
     */
    virtual QString path() const {
        return QString(KEYBOARD);
    }


public Q_SLOTS:
    ///
    /// \brief active
    /// 当模块第一次被点击进入时，active会被调用,如果是插件,重载的时候必须声明为slots,否则加载不了
    virtual void active() {
        mainwindow =new QMainWindow;
        m_frameProxy->pushWidget(this, mainwindow, dccV20::FrameProxyInterface::PushType::Normal);
    }

    ///
    /// \brief active
    /// 当模块被销毁时，deactive会被调用
    virtual void deactive() {

    }

public:
    QMainWindow* mainwindow;

};
}
#endif // FcitxConfigPlugin_H
