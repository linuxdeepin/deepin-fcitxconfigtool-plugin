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
#include <fcitxqtinputmethoditem.h>
QString IMConfig::prefix {QDir::homePath()};

QString IMConfig::defaultIM()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", QString("IMNAME"));
}

bool IMConfig::setDefaultIM(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", "IMNAME", str, false);
}

QString IMConfig::IMSwitchKey()
{
    return configFile(prefix + "/.config/fcitx/config", QString("IMSwitchHotkey"));
}

bool IMConfig::setIMSwitchKey(QString str)
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

QString IMConfig::defaultIMKey()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", QString("HOTKEY"));
}

bool IMConfig::setDefaultIMKey(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", "HOTKEY", str, true);
}

QString IMConfig::IMPluginKey(QString str)
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-implugin.config", str, QString("Setting"));
}

QString IMConfig::configFile(QString filePath, QString group, QString key)
{
    QString read = publisherFunc::readFile(filePath);
    if (read.isEmpty() || key.isEmpty())
        return QString();

    bool lock = false;
    foreach (QString str, read.split("\n")) {
        if (!lock && str.indexOf(group) != -1) {
            lock = true;
        }
        if (lock && str.indexOf(key) != -1) {
            auto list = str.split("=");

            if (list[0].compare(key) != 0 && list[0].compare('#' + key) != 0) {
                continue;
            }

            if (list.count() != 2) {
                return QString();
            } else {
                return list[1];
            }
        }
    }
    return QString();
}

QString IMConfig::configFile(QString filePath, QString key)
{
    QString read = publisherFunc::readFile(filePath);
    if (read.isEmpty() || key.isEmpty())
        return QString();

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
    QString read = publisherFunc::readFile(filePath);
    if (read.isEmpty() || key.isEmpty() || value.isEmpty())
        return false;

    QString file;
    foreach (QString tmp, read.split("\n")) {
        if (tmp.indexOf(key) != -1) {
            if (isHotKey) {
                file += QString(key + "=" + value + "\n").replace("+", "_").toUpper();
            } else {
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
