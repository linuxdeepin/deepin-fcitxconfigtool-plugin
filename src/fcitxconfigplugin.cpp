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
#include "fcitxconfigplugin.h"
#include <QTranslator>

#include "window/imwindow.h"

FcitxConfigPlugin::FcitxConfigPlugin()
{
    m_translator.load(QLocale::system(),
                      QStringLiteral("deepin-fcitxconfigtool-plugin"),
                      QStringLiteral("_"),
                      QStringLiteral("/usr/share/deepin-fcitxconfigtool-plugin/translations"));
    qApp->installTranslator(&m_translator);
    m_imWindow = nullptr;
}

FcitxConfigPlugin::~FcitxConfigPlugin()
{
    qApp->removeTranslator(&m_translator);
    deleteImWindow();
}

void FcitxConfigPlugin::preInitialize(bool sync)
{
    Q_UNUSED(sync);
    qDebug() << __FUNCTION__;
}

QString FcitxConfigPlugin::path() const
{
    //返回控制中心键盘模块
    return KEYBOARD;
}

QString FcitxConfigPlugin::follow() const
{
    //返回三级菜单插入位置
    return "3";
}

void FcitxConfigPlugin::deactive()
{
    deleteImWindow();
}

void FcitxConfigPlugin::initialize()
{
    qDebug() << __FUNCTION__ << QLocale::system().name();
}

void FcitxConfigPlugin::active()
{
    qDebug() << __FUNCTION__;
    m_imWindow = new IMWindow();
    connect(m_imWindow, &IMWindow::requestNextPage, [ = ](QWidget * const w) {
        m_frameProxy->pushWidget(this, w, dccV20::FrameProxyInterface::PushType::CoverTop);
    });
    m_frameProxy->pushWidget(this, m_imWindow, dccV20::FrameProxyInterface::PushType::Normal);
}

const QString FcitxConfigPlugin::name() const
{
    return tr("Input Methods");
}

//这个注释和翻译和使用控制台启动有关
const QString FcitxConfigPlugin::displayName() const
{
    //下面一行注释,和第二行文案有关联是控制中心搜索规范快捷键规范.不可以修改,不可以移动位置,下面三行要在一起
    //~ contents_path /keyboard/Manage Input Methods
    return tr("Input Methods");
}

QIcon FcitxConfigPlugin::icon() const
{
    return QIcon::fromTheme("input_method");
}

QString FcitxConfigPlugin::translationPath() const
{
    return QStringLiteral(":/translations/deepin-fcitxconfigtool-plugin_%1.ts");
}

void FcitxConfigPlugin::deleteImWindow()
{
    if (m_imWindow) {
        m_imWindow->deleteLater();
        m_imWindow = nullptr;
    }
}

