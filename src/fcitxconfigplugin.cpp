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
}
FcitxConfigPlugin::~FcitxConfigPlugin()
{
    qApp->removeTranslator(&m_translator);
    if (imWindow) {
        imWindow->deleteLater();
        imWindow = nullptr;
    }
}

void FcitxConfigPlugin::preInitialize(bool sync)
{
    Q_UNUSED(sync);
    qDebug()<<__FUNCTION__;

}

QString FcitxConfigPlugin::path() const
{
    return KEYBOARD;
}

QString FcitxConfigPlugin::follow() const
{
    return "3";
}

void FcitxConfigPlugin::deactive()
{
    delete imWindow;
}

void FcitxConfigPlugin::initialize()
{
    qDebug()<<__FUNCTION__<<QLocale::system().name();
}

void FcitxConfigPlugin::active()
{
    qDebug()<<__FUNCTION__;
    imWindow = new IMWindow();
    m_frameProxy->pushWidget(this, imWindow, dccV20::FrameProxyInterface::PushType::Normal);
}

const QString FcitxConfigPlugin::name() const
{
    return "manage input methods";
}

const QString FcitxConfigPlugin::displayName() const
{
    QString displayName = QString(tr("Manage Input Methods"));
    if (QLocale::system().language() == QLocale::Chinese) {
        displayName = "输入法";
        if (QLocale::system().country() == QLocale::HongKong) {
            displayName = "输入法";
        } else if (QLocale::system().country() == QLocale::Taiwan) {
            displayName = "输入法";
        } else {
        }
    }
    return displayName;
}


QIcon FcitxConfigPlugin::icon() const
{
    return QIcon::fromTheme("input_method");
}

QString FcitxConfigPlugin::translationPath() const
{
    return QStringLiteral(":/translations/deepin-fcitxconfigtool-plugin_%1.ts");
}
