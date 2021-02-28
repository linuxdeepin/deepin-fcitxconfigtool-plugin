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
#ifndef IMCONFIG_H
#define IMCONFIG_H
#include <QString>

//默认输入法 切换方式 虚拟键盘 默认输入法快捷键
class IMConfig
{
public:
    static QString defaultIM();
    static bool setDefaultIM(QString);
    static QString IMSwitchKey();
    static bool setIMSwitchKey(QString);
    static QString virtualKey();
    static bool setVirtualKey(QString);
    static QString defaultIMKey();
    static bool setDefaultIMKey(QString);
    static QString IMPluginKey(QString);

private:
    static QString configFile(QString filePath, QString key);
    static QString configFile(QString filePath, QString group, QString key);
    static bool setConfigFile(QString filePath, QString key, QString value, bool isHotKey);
    static QString prefix;
};

#endif // IMCONFIG_H
