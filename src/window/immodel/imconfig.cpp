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
#include "imconfig.h"
#include "publisher/publisherfunc.h"
QString IMConfig::prefix {QDir::homePath()};
QString IMConfig::defualtIM()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", QString("IMNAME"));
}

bool IMConfig::setDefualtIM(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", "IMNAME", str, false);
}

QString IMConfig::IMSwitch()
{
    return configFile(prefix + "/.config/fcitx/config", QString("IMSwitchHotkey"));
}

bool IMConfig::setIMSwitch(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/config", "IMSwitchHotkey", str, false);
}

QString IMConfig::virtualKey()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-onboard.config", QString("HOTKEY"));
}

bool IMConfig::setVirtualKey(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-onboard.config", "HOTKEY", str, true);
}

QString IMConfig::defualtIMKey()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", QString("HOTKEY"));
}

bool IMConfig::setDefualtIMKey(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", "HOTKEY", str, true);
}

QString IMConfig::IMConfigCmd(FcitxQtInputMethodItem item)
{
    return QString();
}

QString IMConfig::configFile(QString filePath, QString key)
{
    if (prefix.isEmpty())
        return QString();
    QString read = publisherFunc::readFile(filePath);
    foreach (QString str, read.split("\n")) {
        if (str.indexOf(key) != -1) {
            auto list = str.split("=");
            if (list.count() != 2) {
                return QString();
            } else {
                return list[1];
            }
        }
    }
    return QString();
}

bool IMConfig::setConfigFile(QString filePath, QString key, QString value, bool isHotKey)
{
    if (prefix.isEmpty())
        return false;
    QString read = publisherFunc::readFile(filePath);
    QString file;
    foreach (QString tmp, read.split("\n")) {
        if (tmp.indexOf(key) != -1) {
            if (isHotKey)
                file += QString(key + "=" + value + "\n").replace("+", "_").toUpper();
            else {
                file += QString(key + "=" + value + "\n");
            }
        } else {
            if (!tmp.isEmpty())
                file += tmp + "\n";
        }
    }
    file = file + "\n";
    if (file.isEmpty())
        return false;
    else {
        return publisherFunc::createFile(filePath, file);
    }
}
