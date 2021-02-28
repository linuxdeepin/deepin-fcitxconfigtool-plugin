/*
* Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
*
* Author:     liuwenhao <liuwenhao@uniontech.com>
*
* Maintainer: liuwenhao <liuwenhao@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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

#include "window/imwindow.h"

namespace DCC_NAMESPACE {
class FcitxConfigPlugin : public QObject
    , public DCC_NAMESPACE::ModuleInterface
{
    Q_OBJECT
    Q_INTERFACES(DCC_NAMESPACE::ModuleInterface)
    Q_PLUGIN_METADATA(IID ModuleInterface_iid FILE "ddeInterface/fcitxconfigplugin.json")
public:
    FcitxConfigPlugin();
    FcitxConfigPlugin(FrameProxyInterface *frameProxy)
        : ModuleInterface(frameProxy)
    {
    }
    ~FcitxConfigPlugin()
    {
    }

    /**
    *  preInitialize会在模块初始化时被调用，用于模块在准备阶段进行资源的初始化；
    *  preInitialize不允许进行高资源的操作；
    */
    virtual void preInitialize(bool sync = false, FrameProxyInterface::PushType = FrameProxyInterface::PushType::Normal)
    {
        Q_UNUSED(sync)
    }

    /**
    * initialize初始化相应的模块，参数proxy用于Moudle向Frame信息查询和主动调用；
    * 返回Module的id；
    * initialize的时候不能做资源占用较高的操作；
    */
    virtual void initialize()
    {
    }

    /**
    * reset module settings
    */
    virtual void reset()
    {
        this->icon();
    }

    /**
    * @brief name
    * your module name
    * @return
    */
    virtual const QString name() const
    {
        return QString("Manage Input Methods");
    };

    /**
    * @brief name
    * 模块名，用于显示
    * @return
    */
    virtual const QString displayName() const
    {
        return QString(tr("Manage Input Methods"));
    }

    /**
    * @brief icon
    * get module icon path
    * @return
    */
    virtual QIcon icon() const
    {
        return QIcon::fromTheme("input_method");
    }

    /**
    * @brief translationPath
    * 获取多语言文件的路径，用以搜索
    * @return QString
    */
    virtual QString translationPath() const
    {
        return QString();
    }

    /** @brief showPage
    *   show specified module page
    *   @param pageName
    *   the page name
    */
    virtual void showPage(const QString &pageName)
    {
        Q_UNUSED(pageName);
    }

    /** @brief load
    * 当搜索到相关字段后，lead会被调用
    * 如果可以正常显示则返回 0, 否则返回非0
    */
    virtual int load(const QString &path)
    {
        Q_UNUSED(path);
        return 0;
    }

    virtual QStringList availPage() const
    {
        return QStringList();
    }

    /** @brief path
     * @return 插件级别及二级菜单插件所属模块
     */
    virtual QString path() const
    {
        return QString(KEYBOARD);
    }

    /**
     * @brief follow
     * @return 插件插入位置，可以字符串或者数字
     */
    virtual QString follow() const
    {
        return QString("3");
    }

public Q_SLOTS:
    /**
    *   @brief active
    *   当模块第一次被点击进入时，active会被调用,如果是插件,重载的时候必须声明为slots,否则加载不了
    */
    virtual void active()
    {
        imWindow = new IMWindow;
        m_frameProxy->pushWidget(this, imWindow, dccV20::FrameProxyInterface::PushType::Normal);
    }

    /**
    *   @brief deactive
    *   当模块被销毁时，deactive会被调用
    */
    virtual void deactive()
    {
        delete imWindow;
    }

public:
    IMWindow *imWindow;
};
} // namespace DCC_NAMESPACE
#endif // FcitxConfigPlugin_H
